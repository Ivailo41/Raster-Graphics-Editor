#include "SDLTexture.h"

void SDLTexture::UpdateTexture(const void* pixels, int pitch)
{
	SDL_UpdateTexture(m_Texture, nullptr, pixels, pitch);
}

void* SDLTexture::GetNativeTexture() const
{
	return m_Texture;
}
