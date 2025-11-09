#pragma once
#include "ITexture.h"
#include <memory>
#include "IFrameBuffer.h"

class IRenderer {

public:
	virtual ~IRenderer() = default;

	//virtual bool Init(void* nativeWindow) = 0;
	//virtual void Shutdown() = 0;

	virtual void Clear() = 0;
	virtual void DrawFrame(const IFrameBuffer& framebuffer) = 0;
	virtual void* GetNativeRenderer() = 0;

	virtual std::unique_ptr<ITexture> CreateTexture(int width, int height, TextureScaleMode textureMode) = 0;
	virtual void* getTextureHandle() const = 0;
};