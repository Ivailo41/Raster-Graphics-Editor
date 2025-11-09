#pragma once

class IUIPlatformLayer {

public:
	virtual ~IUIPlatformLayer() = default;

	virtual void Init(void* nativeWindow, void* nativeRenderer) = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void ProcessEvent(void* event) = 0;
};