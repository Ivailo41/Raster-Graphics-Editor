#include <iostream>
#include "Core/IWindow.h"
#include "Core/IRenderer.h"
#include "Core/ITexture.h"

#include "Platforms/SDL/SDLWindow.h"
#include "Platforms/SDL/SDLRenderer.h"
#include "Platforms/SDL/SDLTexture.h"

int main()
{
	const int PIXEL_WIDTH = 20;
	const int PIXEL_HEIGHT = 20;

	// Later make check if SDL is used and then initialize it
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
	}

	// Later create the window based on the chosen platform
	std::unique_ptr<IWindow> window = std::make_unique<SDLWindow>();
	if (!window->Init(800, 600, "SDL Window")) {
		//Make use of other logging in case SDL is not used
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Window Init Error");
		return 1;
	}

	std::unique_ptr<IRenderer> renderer = std::make_unique<SDLRenderer>();
	if (!renderer->Init(window->GetNativeWindow())) {
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Renderer Init Error");
		return 1;
	}

	std::unique_ptr<ITexture> texture = renderer->CreateTexture(PIXEL_WIDTH, PIXEL_HEIGHT, TextureScaleMode::NEAREST);

	Uint32 pixels[PIXEL_WIDTH * PIXEL_HEIGHT];

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

	bool isRunning = true;

	while (isRunning) {

		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}

			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				int mouseX = event.button.x;
				int mouseY = event.button.y;
				SDL_Log("Mouse Clicked at: (%d, %d)", mouseX, mouseY);
			}
		}

		renderer->Clear();

		renderer->RenderTexture(*texture);

		renderer->DrawFrame();
	}
	renderer->Shutdown();
	window->Shutdown();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
