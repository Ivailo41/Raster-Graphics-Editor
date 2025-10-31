#pragma once

#include <SDL3/SDL.h>
#include "../../Core/IWindow.h"

class SDLWindow : public IWindow {

public:
	virtual ~SDLWindow() = default;

	virtual bool Init(unsigned width, unsigned height, const char* title) override;
	virtual void Shutdown() override;

	virtual void PollEvents() override;

	virtual void* GetNativeWindow() const override;

private:
	SDL_Window* m_Window;
	unsigned m_Width;
	unsigned m_Height;
};