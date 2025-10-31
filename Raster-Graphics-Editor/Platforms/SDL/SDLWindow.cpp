#include "SDLWindow.h"

bool SDLWindow::Init(unsigned width, unsigned height, const char* title)
{
	m_Width = width;
	m_Height = height;
	m_Window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);

	if (!m_Window) {
		return false;
	}
	return true;
}

void SDLWindow::Shutdown()
{
	if (m_Window) {
		SDL_DestroyWindow(m_Window);
	}
}

void SDLWindow::PollEvents()
{
}

void* SDLWindow::GetNativeWindow() const
{
	return (void*)m_Window;
}
