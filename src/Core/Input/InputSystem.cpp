#include "InputSystem.h"

void InputSystem::SetKeyDown(KeyCode key)
{
	m_KeysDown[static_cast<int>(key)] = true;
}

void InputSystem::SetKeyUp(KeyCode key)
{
	m_KeysDown[static_cast<int>(key)] = false;
}

void InputSystem::SetMouseButtonDown(MouseButton button)
{
	m_MouseButtonsDown[static_cast<int>(button)] = true;
}

void InputSystem::SetMouseButtonUp(MouseButton button)
{
	m_MouseButtonsDown[static_cast<int>(button)] = false;
}

bool InputSystem::IsKeyDown(KeyCode key) const
{
	return m_KeysDown[static_cast<int>(key)];
}

bool InputSystem::IsMouseButtonDown(MouseButton button) const
{
	return m_MouseButtonsDown[static_cast<int>(button)];
}

