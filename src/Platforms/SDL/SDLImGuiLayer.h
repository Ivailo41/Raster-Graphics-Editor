#pragma once
#include "../../Core/IUIPlatformLayer.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>

class SDLImGuiLayer : public IUIPlatformLayer {

public:
	virtual ~SDLImGuiLayer() override;

	virtual void Init(void* nativeWindow, void* nativeRenderer) override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;

	virtual void ProcessEvent(void* event) override;

private:
	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;
};