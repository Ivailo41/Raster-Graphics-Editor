#pragma once
#include <SDL3/SDL.h>

class IWindow {

public:
	virtual ~IWindow() = default;

	virtual void PollEvents() = 0;

	virtual void* GetNativeWindow() const = 0;

	virtual void GetSize(int* width, int* height) const = 0;
	virtual void GetMousePosition(float* mouseX, float* mouseY) const = 0;
};