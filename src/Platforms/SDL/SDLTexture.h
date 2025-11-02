#pragma once
#include <SDL3/SDL.h>
#include "../../Core/ITexture.h"

class SDLTexture : public ITexture {

public:
	SDLTexture(SDL_Texture* texture) : m_Texture(texture) {}
	virtual ~SDLTexture() = default;
	virtual void UpdateTexture(const void* pixels, int pitch) override;
	virtual void* GetNativeTexture() const override;

	virtual int GetWidth() const override;
	virtual int GetHeight() const override;

private:
	SDL_Texture* m_Texture;
};