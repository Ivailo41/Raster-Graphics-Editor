#pragma once
#include "../../Core/IPlatform.h"
#include "SDLWindow.h"
#include "SDLRenderer.h"

class SDLPlatform : public IPlatform {

public:
	virtual ~SDLPlatform() override = default;

	virtual bool Init() override;
	virtual void Shutdown() override;
	virtual void PollEvents(InputSystem& inputSystem) override;

	virtual bool shouldClose() override;

	virtual std::unique_ptr<IWindow> CreateWindow(int width, int height, const char* title) override;
	virtual std::unique_ptr<IRenderer> CreateRenderer(IWindow* window) override;

private:
	KeyCode TranslateKey(SDL_Scancode keycode);
	MouseButton TranslateMouseButton(SDL_MouseButtonFlags button);

private:
	bool m_ShouldClose = false;
};