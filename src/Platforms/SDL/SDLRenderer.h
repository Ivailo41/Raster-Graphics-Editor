#pragma once

#include <SDL3/SDL.h>
#include "SDLTexture.h"
#include "../../Core/IRenderer.h"
#include <stdexcept>

class SDLRenderer : public IRenderer {

public:
	SDLRenderer(SDL_Window* nativeWindow);
	virtual ~SDLRenderer() override;

	virtual void Clear() override;
	virtual void DrawFrame(const IFrameBuffer& framebuffer) override;
	virtual void* GetNativeRenderer() override;

	virtual std::unique_ptr<ITexture> CreateTexture(int width, int height, TextureScaleMode textureMode) override;
	virtual void* getTextureHandle() const override { return m_Texture; }

private:
	void ensureTextureCreated(int width, int heigth);

private:
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;
};