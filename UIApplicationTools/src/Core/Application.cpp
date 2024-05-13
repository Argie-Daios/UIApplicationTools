#include "Application.h"

#include "Rendering/Renderer.h"
#include "Tools/Input.h"

#include <SDL.h>

Application* Application::s_Instance = nullptr;
std::shared_ptr<Window> Application::s_Window = nullptr;

Application::Application()
	: m_Image(glm::vec2(100, 100))
{
	s_Instance = this;

	s_Window = std::make_shared<Window>("Application", 1440, 810, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	Renderer::Init(s_Window->Get());
}

Application::~Application()
{
	Renderer::Shutdown();
}

void Application::Event(SDL_Event* event)
{
	SDL_PollEvent(event);

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
	
	m_Image.Draw();

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
