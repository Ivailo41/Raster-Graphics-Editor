#pragma once
#include <memory>
#include "IWindow.h"
#include "IRenderer.h"
#include "Input/InputSystem.h"

class IPlatform {
public:
	virtual ~IPlatform() = default;

	virtual bool Init() = 0;
	virtual void Shutdown() = 0;
	virtual bool PollEvent(void* event) const = 0;
	virtual void ProcessEvent(void* event, InputSystem& inputSystem) = 0;

	virtual bool shouldClose() = 0;

	virtual std::unique_ptr<IWindow> CreateWindow(int width, int height, const char* title) = 0;
	virtual std::unique_ptr<IRenderer> CreateRenderer(IWindow* window) = 0;
};