#pragma once
#include "ITexture.h"
#include <memory>

class IRenderer {

public:
	virtual ~IRenderer() = default;

	virtual bool Init(void* nativeWindow) = 0;
	virtual void Shutdown() = 0;

	virtual void Clear() = 0;
	virtual void DrawFrame() = 0;

	virtual void RenderTexture(const ITexture& texture) = 0;
	virtual std::unique_ptr<ITexture> CreateTexture(int width, int height, TextureScaleMode textureMode) = 0;
};