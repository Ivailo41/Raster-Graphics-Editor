#include <iostream>

#include "Core/FrameBuffer.h"

#include "Graphics/CPURasterizer.h"

#include "Platforms/SDL/SDLWindow.h"
#include "Platforms/SDL/SDLRenderer.h"
#include "Platforms/SDL/SDLTexture.h"
#include "Platforms/SDL/SDLPlatform.h"

#include "Graphics/Shapes/Line.h"

#include <vector>

//can be moved to window class
void getClickedPixel(IWindow* window, int pixelWidth, int pixelHeight, unsigned& outX, unsigned& outY) {

	float mouseX;
	float mouseY;
	window->GetMousePosition(&mouseX, &mouseY);
	int windowWidth, windowHeight;
	window->GetSize(&windowWidth, &windowHeight);
	double pixelW = (double)windowWidth / pixelWidth;
	double pixelH = (double)windowHeight / pixelHeight;
	outX = mouseX / pixelW;
	outY = mouseY / pixelH;
}

int main() {

	const int PIXEL_WIDTH = 120;
	const int PIXEL_HEIGHT = 120;

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

	InputSystem inputSystem;

	FrameBuffer frameBuffer(PIXEL_WIDTH, PIXEL_HEIGHT);
	IRasterizer* rasterizer = new CPURasterizer(&frameBuffer);

	std::vector<Shape*> shapes;
	shapes.reserve(100);

	//Demonstration of differ in both algorithms
	shapes.push_back(new Line(10, 20, 110, 70, true, 0x0000FFFF));
	shapes.push_back(new Line(10, 20, 110, 70, false, 0xFF0000FF));

	//Demonstration of differ in both algorithms
	shapes.push_back(new Line(32, 10, 62, 110, true, 0x00FF00FF));
	shapes.push_back(new Line(30, 10, 60, 110, false, 0xFFFF00FF));

	//temporary variable to check on mouse up event
	bool mouseDown = false;

	//temporary variables to store the preview line start and end points
	unsigned int x0, x1, y0, y1;

	// Main loop
	while (!platform->shouldClose()) {

		platform->PollEvents(inputSystem);

		frameBuffer.Clear(0xFF000000); // Clear to black
		renderer->Clear();
		
		if(inputSystem.IsMouseButtonDown(MouseButton::LEFT)) {

			if (!mouseDown) {
				getClickedPixel(window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, x0, y0);
			}

			mouseDown = true;

			unsigned horizontalTileIndex;
			unsigned verticalTileIndex;

			getClickedPixel(window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, horizontalTileIndex, verticalTileIndex);

			rasterizer->DrawLineBresenham(x0, y0, horizontalTileIndex, verticalTileIndex, 0xFFFFFFFF);
		}

		if (mouseDown && !inputSystem.IsMouseButtonDown(MouseButton::LEFT)) {

			getClickedPixel(window.get(), PIXEL_WIDTH, PIXEL_HEIGHT, x1, y1);

			shapes.push_back(new Line(x0, y0, x1, y1, true, 0xFFFFFFFF));

			mouseDown = false;
		}

		if(inputSystem.IsKeyDown(KeyCode::KeyCode_E)) {
			shapes.clear();
		}

		//For each shape rasterize shape to framebuffer
		for (const Shape* shape : shapes) {
			shape->Draw(rasterizer);
		}

		renderer->DrawFrame(frameBuffer);
	}
	platform->Shutdown();
}
