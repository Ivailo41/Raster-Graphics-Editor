#include "SDLRenderer.h"

SDLRenderer::SDLRenderer(SDL_Window* nativeWindow) : m_Texture(nullptr)
{
	if (!nativeWindow) {
		throw std::invalid_argument("SDLRenderer requires a valid SDL_Window pointer");
	}

	Uint32 flags = SDL_GetWindowFlags(nativeWindow);
	if (flags == 0) {
		throw std::runtime_error("Provided window is not a valid SDL_Window");
	}

	m_Renderer = SDL_CreateRenderer(nativeWindow, NULL);
	if (!m_Renderer) {
		throw std::runtime_error("Failed to create SDL Renderer");
	}
}

SDLRenderer::~SDLRenderer()
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

void SDLRenderer::DrawFrame(const IFrameBuffer& framebuffer)
{
	ensureTextureCreated(framebuffer.GetWidth(), framebuffer.GetHeight());
	SDL_UpdateTexture(m_Texture, NULL, framebuffer.GetPixels(), framebuffer.GetWidth() * sizeof(uint32_t));
	//SDL_RenderTexture(m_Renderer, m_Texture, NULL, NULL);
	SDL_RenderPresent(m_Renderer);
}

void* SDLRenderer::GetNativeRenderer()
{
	return m_Renderer;
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

void SDLRenderer::ensureTextureCreated(int width, int heigth)
{
	if (m_Texture) {
		if(m_Texture->w == width && m_Texture->h == heigth) {
			return;
		}
	}

	SDL_DestroyTexture(m_Texture);
	m_Texture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, heigth);
	SDL_SetTextureScaleMode(m_Texture, SDL_SCALEMODE_NEAREST);
}
