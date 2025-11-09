#include "SDLImGuiLayer.h"

SDLImGuiLayer::~SDLImGuiLayer()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void SDLImGuiLayer::Init(void* nativeWindow, void* nativeRenderer)
{
	m_Renderer = (SDL_Renderer*)nativeRenderer;
	m_Window = (SDL_Window*)nativeWindow;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

	ImGui::StyleColorsDark();

	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale);
	style.FontScaleDpi = main_scale;

	ImGui_ImplSDL3_InitForSDLRenderer(m_Window, m_Renderer);
	ImGui_ImplSDLRenderer3_Init(m_Renderer);
}

void SDLImGuiLayer::BeginFrame()
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();
}

void SDLImGuiLayer::EndFrame()
{
	ImGui::Render();
	//SDL_SetRenderScale(m_Renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	//SDL_SetRenderDrawColorFloat(m_Renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_Renderer);
}

void SDLImGuiLayer::ProcessEvent(void* event)
{
	SDL_Event* sdlEvent = static_cast<SDL_Event*>(event);
	ImGui_ImplSDL3_ProcessEvent(sdlEvent);
}
