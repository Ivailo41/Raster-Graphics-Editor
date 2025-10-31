#pragma once

#include <SDL3/SDL.h>
#include "../../Core/IWindow.h"
#include <stdexcept>

class SDLWindow : public IWindow {

public:
	SDLWindow(unsigned width, unsigned height, const char* title);
	virtual ~SDLWindow();

	//virtual bool Init(unsigned width, unsigned height, const char* title) override;
	//virtual void Shutdown() override;

	virtual void PollEvents() override;

	virtual void* GetNativeWindow() const override;

	virtual void GetSize(int* width, int* height) const override;
	virtual void GetMousePosition(float* mouseX, float* mouseY) const override;

private:
	SDL_Window* m_Window;
	unsigned m_Width;
	unsigned m_Height;
};