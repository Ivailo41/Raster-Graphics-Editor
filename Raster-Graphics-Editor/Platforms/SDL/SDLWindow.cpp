#include "SDLWindow.h"

SDLWindow::SDLWindow(unsigned width, unsigned height, const char* title)
{
	m_Width = width;
	m_Height = height;
	m_Window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);

	if (!m_Window) {
		throw std::runtime_error("Failed to create SDL Window");
	}
}

SDLWindow::~SDLWindow()
{
	if (m_Window) {
		SDL_DestroyWindow(m_Window);
	}
}

//bool SDLWindow::Init(unsigned width, unsigned height, const char* title)
//{
//	m_Width = width;
//	m_Height = height;
//	m_Window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
//
//	if (!m_Window) {
//		return false;
//	}
//	return true;
//}

//void SDLWindow::Shutdown()
//{
//	if (m_Window) {
//		SDL_DestroyWindow(m_Window);
//	}
//}

void SDLWindow::PollEvents()
{
}

void* SDLWindow::GetNativeWindow() const
{
	return (void*)m_Window;
}

void SDLWindow::GetSize(int* width, int* height) const
{
	SDL_GetWindowSize(m_Window, width, height);
}

void SDLWindow::GetMousePosition(float* mouseX, float* mouseY) const
{
	SDL_GetMouseState(mouseX, mouseY);
}
