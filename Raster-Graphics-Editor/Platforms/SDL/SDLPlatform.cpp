#include "SDLPlatform.h"

bool SDLPlatform::Init()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		return false;
	}

	return true;
}

void SDLPlatform::Shutdown()
{
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void SDLPlatform::PollEvents(InputSystem& inputSystem)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT:
				m_ShouldClose = true;
				break;
			case SDL_EVENT_KEY_DOWN:
				inputSystem.SetKeyDown(TranslateKey(event.key.scancode));
				break;
			case SDL_EVENT_KEY_UP:
				inputSystem.SetKeyUp(TranslateKey(event.key.scancode));
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				inputSystem.SetMouseButtonDown(TranslateMouseButton(event.button.button));
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				inputSystem.SetMouseButtonUp(TranslateMouseButton(event.button.button));
				break;
		}
	}
}

bool SDLPlatform::shouldClose()
{
	return m_ShouldClose;
}

std::unique_ptr<IWindow> SDLPlatform::CreateWindow(int width, int height, const char* title)
{
	return std::make_unique<SDLWindow>(width, height, title);
}

std::unique_ptr<IRenderer> SDLPlatform::CreateRenderer(IWindow* window)
{
	return std::make_unique<SDLRenderer>(static_cast<SDL_Window*>(window->GetNativeWindow()));
}

KeyCode SDLPlatform::TranslateKey(SDL_Scancode keycode)
{
	switch (keycode) {

		case SDL_SCANCODE_1: return KeyCode::KeyCode_1;
		case SDL_SCANCODE_2: return KeyCode::KeyCode_2;
		case SDL_SCANCODE_3: return KeyCode::KeyCode_3;
		case SDL_SCANCODE_4: return KeyCode::KeyCode_4;
		case SDL_SCANCODE_5: return KeyCode::KeyCode_5;
		case SDL_SCANCODE_6: return KeyCode::KeyCode_6;
		case SDL_SCANCODE_7: return KeyCode::KeyCode_7;
		case SDL_SCANCODE_8: return KeyCode::KeyCode_8;
		case SDL_SCANCODE_9: return KeyCode::KeyCode_9;
		case SDL_SCANCODE_0: return KeyCode::KeyCode_0;

		case SDL_SCANCODE_A: return KeyCode::KeyCode_A;
		case SDL_SCANCODE_B: return KeyCode::KeyCode_B;
		case SDL_SCANCODE_C: return KeyCode::KeyCode_C;
		case SDL_SCANCODE_D: return KeyCode::KeyCode_D;
		case SDL_SCANCODE_E: return KeyCode::KeyCode_E;
		case SDL_SCANCODE_F: return KeyCode::KeyCode_F;
		case SDL_SCANCODE_G: return KeyCode::KeyCode_G;
		case SDL_SCANCODE_H: return KeyCode::KeyCode_H;
		case SDL_SCANCODE_I: return KeyCode::KeyCode_I;
		case SDL_SCANCODE_J: return KeyCode::KeyCode_J;
		case SDL_SCANCODE_K: return KeyCode::KeyCode_K;
		case SDL_SCANCODE_L: return KeyCode::KeyCode_L;
		case SDL_SCANCODE_M: return KeyCode::KeyCode_M;
		case SDL_SCANCODE_N: return KeyCode::KeyCode_N;
		case SDL_SCANCODE_O: return KeyCode::KeyCode_O;
		case SDL_SCANCODE_P: return KeyCode::KeyCode_P;
		case SDL_SCANCODE_Q: return KeyCode::KeyCode_Q;
		case SDL_SCANCODE_R: return KeyCode::KeyCode_R;
		case SDL_SCANCODE_S: return KeyCode::KeyCode_S;
		case SDL_SCANCODE_T: return KeyCode::KeyCode_T;
		case SDL_SCANCODE_U: return KeyCode::KeyCode_U;
		case SDL_SCANCODE_V: return KeyCode::KeyCode_V;
		case SDL_SCANCODE_W: return KeyCode::KeyCode_W;
		case SDL_SCANCODE_X: return KeyCode::KeyCode_X;
		case SDL_SCANCODE_Y: return KeyCode::KeyCode_Y;
		case SDL_SCANCODE_Z: return KeyCode::KeyCode_Z;
	}
}

MouseButton SDLPlatform::TranslateMouseButton(SDL_MouseButtonFlags button)
{
	switch (button) {
		case SDL_BUTTON_LEFT: return MouseButton::LEFT;
		case SDL_BUTTON_RIGHT: return MouseButton::RIGHT;
		case SDL_BUTTON_MIDDLE: return MouseButton::MIDDLE;
		case SDL_BUTTON_X1: return MouseButton::MOUSE4;
		case SDL_BUTTON_X2: return MouseButton::MOUSE5;
	}
}
