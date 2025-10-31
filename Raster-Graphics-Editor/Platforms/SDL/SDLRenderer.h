#pragma once

#include <SDL3/SDL.h>
#include "SDLTexture.h"
#include "../../Core/IRenderer.h"
#include <stdexcept>

class SDLRenderer : public IRenderer {

public:
	SDLRenderer(SDL_Window* nativeWindow);
	virtual ~SDLRenderer() override;

	//virtual bool Init(void* nativeWindow) override;
	//virtual void Shutdown() override;

	virtual void Clear() override;
	virtual void DrawFrame() override;

	virtual void RenderTexture(const ITexture& texture) override;
	virtual std::unique_ptr<ITexture> CreateTexture(int width, int height, TextureScaleMode textureMode) override;

private:
	SDL_Renderer* m_Renderer;
};