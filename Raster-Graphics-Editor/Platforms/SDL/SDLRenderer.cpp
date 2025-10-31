#include "SDLRenderer.h"

bool SDLRenderer::Init(void* nativeWindow)
{
	m_Renderer = SDL_CreateRenderer(static_cast<SDL_Window*>(nativeWindow), NULL);
	if (!m_Renderer) {
		return false;
	}
	return true;
}

void SDLRenderer::Shutdown()
{
	if (m_Renderer) {
		SDL_DestroyRenderer(m_Renderer);
	}
}

void SDLRenderer::Clear()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);
}

void SDLRenderer::DrawFrame()
{
	SDL_RenderPresent(m_Renderer);
}

void SDLRenderer::RenderTexture(const ITexture& texture)
{
	SDL_RenderTexture(m_Renderer, static_cast<SDL_Texture*>(texture.GetNativeTexture()), NULL, NULL);
}

std::unique_ptr<ITexture> SDLRenderer::CreateTexture(int width, int height, TextureScaleMode textureMode)
{
	SDL_Texture* sdlTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!sdlTexture) {
		return nullptr;
	}
	SDL_SetTextureScaleMode(sdlTexture, (SDL_ScaleMode)textureMode);

	return std::make_unique<SDLTexture>(sdlTexture);
}
