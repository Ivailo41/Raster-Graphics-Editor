#pragma once
#include <SDL3/SDL.h>

class IWindow {

public:
	virtual ~IWindow() = default;
	
	virtual bool Init(unsigned width, unsigned height, const char* title) = 0;
	virtual void Shutdown() = 0;

	virtual void PollEvents() = 0;

	virtual void* GetNativeWindow() const = 0;
};