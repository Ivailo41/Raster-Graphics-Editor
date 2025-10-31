#pragma once
#include "InputCodes.h"

class InputSystem {

public:
	void SetKeyDown(KeyCode key);
	void SetKeyUp(KeyCode key);

	void SetMouseButtonDown(MouseButton button);
	void SetMouseButtonUp(MouseButton button);

	bool IsKeyDown(KeyCode key) const;
	bool IsMouseButtonDown(MouseButton button) const;

private:
	bool m_KeysDown[256] = { false };
	bool m_MouseButtonsDown[8] = { false };
};