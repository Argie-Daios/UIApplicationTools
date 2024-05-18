#include "Application.h"

#include "Rendering/Renderer.h"
#include "Tools/AssetManager.h"
#include "Tools/Input.h"

#include <SDL.h>

Application* Application::s_Instance = nullptr;
std::shared_ptr<Window> Application::s_Window = nullptr;

Application::Application()
{
	s_Instance = this;

	s_Window = CreateUIReferencePointer<Window>("Application", 1440, 810,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	Renderer::Init(s_Window->Get());
	AssetManager::Init();

	AssetManager::LoadTexture("ResidentEvil", "assets/RE.png");
	AssetManager::LoadFont("Arial", "assets/ARIAL.TTF", 90);

	m_Image = CreateUIScopePointer<Image>(Vector2f(100, 100), "ResidentEvil", Vector2f(700, 500));
	m_Text = CreateUIScopePointer<Text>(Vector2f(900, 500), "Jill Valentine", "Arial", ColorRGB(0, 0, 255));
}

Application::~Application()
{
	Renderer::Shutdown();
	AssetManager::Shutdown();
}

void Application::Event(SDL_Event* event)
{
	Input::PollEvent();

	switch (event->type)
	{
	case SDL_QUIT:
	{
		m_Running = false;
		break;
	}
	}
}

void Application::Update()
{

}

void Application::Draw()
{
	Renderer::Begin();
	
	m_Image->Draw();
	m_Text->Draw();

	Renderer::End();
}

void Application::Run()
{
	while (m_Running)
	{
		Event(&Input::Event());
		Update();
		Draw();
	}
}