#include "SDLTexture.h"

void SDLTexture::UpdateTexture(const void* pixels, int pitch)
{
	SDL_UpdateTexture(m_Texture, nullptr, pixels, pitch);
}

void* SDLTexture::GetNativeTexture() const
{
	return m_Texture;
}

int SDLTexture::GetWidth() const
{
	return m_Texture ? m_Texture->w : 0;
}

int SDLTexture::GetHeight() const
{
	return m_Texture ? m_Texture->h : 0;
}
