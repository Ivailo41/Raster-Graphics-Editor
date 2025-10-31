#include <iostream>
#include "Core/IWindow.h"
#include "Core/IRenderer.h"
#include "Core/ITexture.h"
#include "Core/IPlatform.h"

#include "Platforms/SDL/SDLWindow.h"
#include "Platforms/SDL/SDLRenderer.h"
#include "Platforms/SDL/SDLTexture.h"
#include "Platforms/SDL/SDLPlatform.h"

int main()
{
	const int PIXEL_WIDTH = 100;
	const int PIXEL_HEIGHT = 100;

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

	std::unique_ptr<ITexture> texture = renderer->CreateTexture(PIXEL_WIDTH, PIXEL_HEIGHT, TextureScaleMode::NEAREST);

	Uint32* pixels = new Uint32[PIXEL_WIDTH * PIXEL_HEIGHT];

	// Fill pixel array with a gradient
	for (int y = 0; y < PIXEL_HEIGHT; ++y) {
		for (int x = 0; x < PIXEL_WIDTH; ++x) {
			Uint8 r = (Uint8)((float)x / PIXEL_WIDTH * 255);
			Uint8 g = (Uint8)((float)y / PIXEL_HEIGHT * 255);
			Uint8 b = 128;
			pixels[y * PIXEL_WIDTH + x] = (r << 24) | (g << 16) | (b << 8) | 255;
		}
	}

	texture->UpdateTexture(pixels, PIXEL_WIDTH * sizeof(Uint32));

	// Main loop
	while (!platform->shouldClose()) {

		platform->PollEvents(inputSystem);

		SDL_Event event;
		
		if(inputSystem.IsMouseButtonDown(MouseButton::LEFT)) {
			float mouseX;
			float mouseY;
			window->GetMousePosition(&mouseX, &mouseY);

			int windowWidth, windowHeight;
			window->GetSize(&windowWidth, &windowHeight);

			double pixelWidth = (double)windowWidth / PIXEL_WIDTH;
			double pixelHeight = (double)windowHeight / PIXEL_HEIGHT;

			unsigned horizontalTileIndex = mouseX / pixelWidth;
			unsigned verticalTileIndex = mouseY / pixelHeight;
			// Change the color of the pixel to white on mouse down
			pixels[verticalTileIndex * PIXEL_WIDTH + horizontalTileIndex] = 0xFFFFFFFF;
			texture->UpdateTexture(pixels, PIXEL_WIDTH * sizeof(Uint32));
		}

		renderer->Clear();

		renderer->RenderTexture(*texture);

		renderer->DrawFrame();
	}

	delete[] pixels;
	platform->Shutdown();
}
