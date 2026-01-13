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
#include "Graphics/Shapes/Polygon.h"
#include "Graphics/Shapes/Rectangle.h"

#include <vector>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include <random>
#include <math.h>

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

int LiangBarsky2DClip(unsigned& x0, unsigned& y0, unsigned& x1, unsigned& y1, unsigned xmin, unsigned ymin, unsigned xmax, unsigned ymax) {
	if (xmin >= xmax || ymin >= ymax)
		return 0;

	float fx0 = static_cast<float>(x0);
	float fy0 = static_cast<float>(y0);
	float fx1 = static_cast<float>(x1);
	float fy1 = static_cast<float>(y1);

	float dx = fx1 - fx0;
	float dy = fy1 - fy0;

	float p[4] = { -dx, dx, -dy, dy };
	float q[4] = { fx0 - xmin, xmax - fx0, fy0 - ymin, ymax - fy0 };

	float u1 = 0.0f, u2 = 1.0f;

	for (int i = 0; i < 4; ++i) {
		if (fabs(p[i]) < 1e-6f) {
			if (q[i] < 0.0f)
				return 0;
		}
		else {
			float r = q[i] / p[i];
			if (p[i] < 0.0f) {
				if (r > u2) return 0;
				if (r > u1) u1 = r;
			}
			else {
				if (r < u1) return 0;
				if (r < u2) u2 = r;
			}
		}
	}

	if (u1 > u2)
		return 0;

	float nx0 = fx0 + u1 * dx;
	float ny0 = fy0 + u1 * dy;
	float nx1 = fx0 + u2 * dx;
	float ny1 = fy0 + u2 * dy;

	x0 = static_cast<unsigned>(std::round(nx0));
	y0 = static_cast<unsigned>(std::round(ny0));
	x1 = static_cast<unsigned>(std::round(nx1));
	y1 = static_cast<unsigned>(std::round(ny1));

	return 1;
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

	Rectangle* rect = new Rectangle(10, 10, 50, 50, 0xFFFFFFFF);
	Line* line = new Line(60, 60, 100, 100, 0, 0xFF0000FF);

	std::vector<Shape*> shapes;

	shapes.push_back(rect);
	shapes.push_back(line);

	shapes.reserve(100);

	//temporary variable to check on mouse up event
	bool mouseDown = false;

	//temporary variables to store the preview line start and end points
	unsigned int x0, x1, y0, y1;

	bool drawClippedLine = false;

	float progress = 1.0f;
	float progress2 = 1.0f;
	unsigned line1Start[2] = { 10, 20 };
	unsigned line1End[2] = { 110, 70 };

	unsigned rectangleStart[2] = { 0, 0 };
	unsigned rectangleEnd[2] = { 0, 0 };

	unsigned clippedLineStart[2] = { 0, 0 };
	unsigned clippedLineEnd[2] = { 0, 0 };

	unsigned int reactangleX, rectangleY, rectangleWidth, rectangleHeight;

	SDL_Texture* myTexture;
	
	ImVec2 canvasSize, canvasOffset;

	std::vector<point2d> polygonPoints;
	std::vector<point2d> polygonFills;

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

		//For each shape rasterize shape to framebuffer
		for (const Shape* shape : shapes) {
			shape->Draw(rasterizer);
		}

		for (size_t i = 0; i < polygonPoints.size(); ++i) {
			const point2d& p1 = polygonPoints[i];
			const point2d& p2 = polygonPoints[(i + 1) % polygonPoints.size()]; // Wrap around to the first point
			rasterizer->DrawLineBresenham(p1.x, p1.y, p2.x, p2.y, 0x00FF00FF, 1.0f);
		}

		for (const point2d& fillPoint : polygonFills) {
			rasterizer->SimpleBoundaryFill(fillPoint.x, fillPoint.y, 0x0000FFFF, 0x00FF00FF, progress, 0);
		}

		if(inputSystem.IsMouseButtonDown(MouseButton::RIGHT)) {


			if (!mouseDown) {
				getClickedPixel(canvasSize, canvasOffset, window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, reactangleX, rectangleY);
				//polygonPoints.push_back({ (int)x0, (int)y0 });
				std::cout << "Rectangle Start X: " << reactangleX << " Y: " << rectangleY << std::endl;
			}

			mouseDown = true;

			unsigned horizontalTileIndex;
			unsigned verticalTileIndex;

			getClickedPixel(canvasSize, canvasOffset, window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, horizontalTileIndex, verticalTileIndex);

			rasterizer->DrawRectangle(reactangleX, rectangleY, horizontalTileIndex, verticalTileIndex, 0xFFFFFFFF, progress2);
		}

		if (mouseDown && !inputSystem.IsMouseButtonDown(MouseButton::RIGHT)) {

			getClickedPixel(canvasSize, canvasOffset, window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, x1, y1);

			mouseDown = false;
		}
		
		if (drawClippedLine) {
			rasterizer->DrawLineSimple(clippedLineStart[0], clippedLineStart[1], clippedLineEnd[0], clippedLineEnd[1], 0x0000FFFF, progress2);
		}

		if(inputSystem.IsKeyDown(KeyCode::KeyCode_E)) {
			shapes.clear();
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
		if (ImGui::SliderFloat("Progress - Line", &progress, 0.0f, 1.0f)) {
			line->setProgress(progress);
		}
		if (ImGui::SliderFloat("Progress - Clipped Line", &progress2, 0.0f, 1.0f)) {
			
		}
		if (ImGui::SliderInt2("Line1 Start", (int*)line1Start, 0, PIXEL_WIDTH)) {
			line->SetStart(line1Start[0], line1Start[1]);

			clippedLineStart[0] = line1Start[0];
			clippedLineStart[1] = line1Start[1];
			clippedLineEnd[0] = line1End[0];
			clippedLineEnd[1] = line1End[1];

			drawClippedLine = LiangBarsky2DClip(clippedLineStart[0], clippedLineStart[1], clippedLineEnd[0], clippedLineEnd[1], rect->getMinX(), rect->getMinY(), rect->getMaxX(), rect->getMaxY());
		}
		if (ImGui::SliderInt2("Line1 End", (int*)line1End, 0, PIXEL_WIDTH)) {
			line->SetEnd(line1End[0], line1End[1]);

			clippedLineStart[0] = line1Start[0];
			clippedLineStart[1] = line1Start[1];
			clippedLineEnd[0] = line1End[0];
			clippedLineEnd[1] = line1End[1];

			drawClippedLine = LiangBarsky2DClip(clippedLineStart[0], clippedLineStart[1], clippedLineEnd[0], clippedLineEnd[1], rect->getMinX(), rect->getMinY(), rect->getMaxX(), rect->getMaxY());
		}
		if (ImGui::SliderInt2("Rectangle Start", (int*)rectangleStart, 0, PIXEL_WIDTH)) {
			rect->setStart(rectangleStart[0], rectangleStart[1]);

			clippedLineStart[0] = line1Start[0];
			clippedLineStart[1] = line1Start[1];
			clippedLineEnd[0] = line1End[0];
			clippedLineEnd[1] = line1End[1];

			drawClippedLine = LiangBarsky2DClip(clippedLineStart[0], clippedLineStart[1], clippedLineEnd[0], clippedLineEnd[1], rect->getMinX(), rect->getMinY(), rect->getMaxX(), rect->getMaxY());
		}
		if (ImGui::SliderInt2("Rectangle End", (int*)rectangleEnd, 0, PIXEL_WIDTH)) {
			rect->setEnd(rectangleEnd[0], rectangleEnd[1]);

			clippedLineStart[0] = line1Start[0];
			clippedLineStart[1] = line1Start[1];
			clippedLineEnd[0] = line1End[0];
			clippedLineEnd[1] = line1End[1];

			drawClippedLine = LiangBarsky2DClip(clippedLineStart[0], clippedLineStart[1], clippedLineEnd[0], clippedLineEnd[1], rect->getMinX(), rect->getMinY(), rect->getMaxX(), rect->getMaxY());
		}
		if (ImGui::Button("Reset polygon fill")) {
			polygonFills.clear();
		}
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
