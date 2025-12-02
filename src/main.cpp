#include <iostream>

#include "Core/FrameBuffer.h"

#include "Graphics/CPURasterizer.h"

#include "Platforms/SDL/SDLWindow.h"
#include "Platforms/SDL/SDLRenderer.h"
#include "Platforms/SDL/SDLTexture.h"
#include "Platforms/SDL/SDLPlatform.h"
#include "Platforms/SDL/SDLImGuiLayer.h"

#include "UI/UIManager.h"

#include "Graphics/Shapes/Line.h"
#include "Graphics/Shapes/Circle.h"

#include <vector>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include <chrono>
#include <random>
#include <math.h>
using namespace std::chrono;

void getClickedPixel(ImVec2 canvasSize, ImVec2 canvasOffset, IWindow* window, int pixelWidth, int pixelHeight, unsigned& outX, unsigned& outY) {

	float mouseX;
	float mouseY;
	window->GetMousePosition(&mouseX, &mouseY);
	int windowWidth, windowHeight;
	window->GetSize(&windowWidth, &windowHeight);
	double pixelW = (double)canvasSize.x / pixelWidth;
	double pixelH = (double)canvasSize.y / pixelHeight;
	outX = (mouseX - canvasOffset.x) / pixelW;
	outY = (mouseY - canvasOffset.y) / pixelH;
}

unsigned calcDistance(int x0, int y0, int x1, int y1) {
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	return 0.9412f * std::max(dx, dy) + 0.4142f * std::min(dx, dy);
}

int main() {

	int PIXEL_WIDTH = 120;
	int PIXEL_HEIGHT = 120;
	int res[2] = { PIXEL_WIDTH, PIXEL_HEIGHT };

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	IPlatform* platform = new SDLPlatform();

	// Later make check if SDL is used and then initialize it
	if (!platform || !platform->Init()) {
		std::cerr << "Failed to initialize platform." << std::endl;
		return -1;
	}

	std::unique_ptr<IWindow> window;
	std::unique_ptr<IRenderer> renderer;

	try {
		window = platform->CreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raster Graphics Editor");

	} 
	catch (const std::exception& e) {
		std::cerr << "Failed to create window: " << e.what() << std::endl;
		return -1;
	}
	
	try {
		renderer = platform->CreateRenderer(window.get());
	} 
	catch (const std::exception& e) {
		std::cerr << "Failed to create renderer: " << e.what() << std::endl;
		return -1;
	}

	std::unique_ptr<IUIPlatformLayer> uiLayer = std::make_unique<SDLImGuiLayer>();
	UIManager uiManager;

	uiLayer->Init(window->GetNativeWindow(), renderer->GetNativeRenderer());

	InputSystem inputSystem;

	FrameBuffer frameBuffer(PIXEL_WIDTH, PIXEL_HEIGHT);
	IRasterizer* rasterizer = new CPURasterizer(&frameBuffer);

	std::vector<Shape*> shapes;
	shapes.reserve(100);

	//temporary variable to check on mouse up event
	bool mouseDown = false;

	//temporary variables to store the preview line start and end points
	unsigned int x0, x1, y0, y1;

	float progress = 1.0f;
	unsigned line1Start[2] = { 10, 20 };
	unsigned line1End[2] = { 110, 70 };

	unsigned circleCenter[2] = { 60, 60 };
	unsigned circleRadius = 30;

	bool bold = false;

	long long stressTestResult = 0;

	SDL_Texture* myTexture;
	
	ImVec2 canvasSize, canvasOffset;

	// Main loop
	while (!platform->shouldClose()) {

		myTexture = static_cast<SDL_Texture*>(renderer->getTextureHandle());
		int winW, winH;
		window->GetSize(&winW, &winH);

		SDL_Event event;
		while (platform->PollEvent(&event)) {
			platform->ProcessEvent(&event, inputSystem);
			uiLayer->ProcessEvent(&event);
		}

		frameBuffer.Clear(0xFF000000); // Clear to black
		renderer->Clear();
		
		//rasterizer->DrawLineBresenham(line1Start[0], line1Start[1], line1End[0], line1End[1], 0x0000FFFF, progress);
		//rasterizer->DrawLineSimple(line1Start[0], line1Start[1], line1End[0], line1End[1], 0xFF0000FF, progress);

		rasterizer->DrawCircleMidPoint(circleCenter[0], circleCenter[1], circleRadius, 0x00FF00FF, progress, bold);

		if(inputSystem.IsMouseButtonDown(MouseButton::RIGHT)) {


			if (!mouseDown) {
				getClickedPixel(canvasSize, canvasOffset, window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, x0, y0);
			}

			mouseDown = true;

			unsigned horizontalTileIndex;
			unsigned verticalTileIndex;

			getClickedPixel(canvasSize, canvasOffset, window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, horizontalTileIndex, verticalTileIndex);

			rasterizer->DrawCircleMidPoint(x0, y0, calcDistance(x0,y0,horizontalTileIndex,verticalTileIndex), 0xFF00FFFF, 1, bold);
		}

		if (mouseDown && !inputSystem.IsMouseButtonDown(MouseButton::RIGHT)) {

			getClickedPixel(canvasSize, canvasOffset, window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, x1, y1);

			//shapes.push_back(new Line(x0, y0, x1, y1, true, 0xFFFFFFFF));
			shapes.push_back(new Circle(x0, y0, calcDistance(x0, y0, x1, y1), 0xFF00FFFF, bold));

			mouseDown = false;
		}

		if(inputSystem.IsKeyDown(KeyCode::KeyCode_E)) {
			shapes.clear();
		}

		//For each shape rasterize shape to framebuffer
		for (const Shape* shape : shapes) {
			shape->Draw(rasterizer);
		}

		uiLayer->BeginFrame();
		uiManager.RenderUI(progress);
		ImGui::Begin("Hello, world!");

		ImGui::SliderInt2("Resolution", res, 10, 1920);
		if (ImGui::Button("Change Resolution")) {
			PIXEL_WIDTH = res[0];
			PIXEL_HEIGHT = res[1];
			frameBuffer.SetSize(PIXEL_WIDTH, PIXEL_HEIGHT);
		}
		ImGui::SliderFloat("Progress", &progress, 0.0f, 1.0f);
		ImGui::SliderInt2("Line1 Start", (int*)line1Start, 0, PIXEL_WIDTH);
		ImGui::SliderInt2("Line1 End", (int*)line1End, 0, PIXEL_WIDTH);
		ImGui::SliderInt2("Circle center", (int*)circleCenter, 0, PIXEL_WIDTH);
		ImGui::SliderInt("Circle Radius", (int*)&circleRadius, 0, PIXEL_WIDTH);
		ImGui::Checkbox("Bold Circle", &bold);
		if (ImGui::Button("Test 100k lines draw")) {

			std::random_device rd; // obtain a random number from hardware
			std::mt19937 gen(rd()); // seed the generator
			std::uniform_int_distribution<> distr(0, std::max(PIXEL_WIDTH, PIXEL_HEIGHT)); // define the range

			auto start = high_resolution_clock::now();
			for (size_t i = 0; i < 100000; i++)
			{
				rasterizer->DrawLineBresenham(distr(gen), distr(gen), distr(gen), distr(gen), 0xFFFFFFFF, 1.0);
			}
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);
			stressTestResult = duration.count();
		}
		ImGui::Text("Calculation 100k Lines duration: %i ms", stressTestResult);
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Texture Preview", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		canvasOffset = ImGui::GetWindowPos();
		canvasSize = ImGui::GetWindowSize();

		ImVec2 contentRegion = ImGui::GetContentRegionAvail();
		// Convert SDL_Texture* to ImTextureID
		ImTextureID texID = (ImTextureID)myTexture;

		// Specify UVs from top-left (0,0) to bottom-right (1,1)
		ImVec2 texSize((float)winW, (float)winH);
		ImGui::Image(texID, contentRegion, ImVec2(0, 0), ImVec2(1, 1));

		ImGui::End();
		ImGui::PopStyleVar();

		uiLayer->EndFrame();
		renderer->DrawFrame(frameBuffer);

	}

	platform->Shutdown();
}
