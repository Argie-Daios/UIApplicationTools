#include "Application.h"

#include "Rendering/Renderer.h"
#include "Tools/AssetManager.h"
#include "Tools/Input.h"
#include "Macros.h"
#include "Math/Positioner.h"
#include "Time.h"
#include "PerformanceManager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <algorithm>

Application* Application::s_Instance = nullptr;
UIReferencePointer<Window> Application::s_Window = nullptr;

Application::Application()
{
	s_Instance = this;

	s_Window = CreateUIReferencePointer<Window>("Application", 1440, 810,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	Renderer::Init(s_Window->Get());
	AssetManager::Init();
	Time::Init();

	PerformanceManager::SetFPSCap(FPS_CAPS::FPS_60);
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

void Application::Begin()
{

}

void Application::Update()
{
	GetCurrentScene()->ForEach([](UIItem* item) { 
		if (UIWidget* casted = Cast<UIWidget*>(item))
		{
			casted->Update();
		}
	});
	GetCurrentScene()->Update();
}

void Application::Draw()
{
	Renderer::Begin();

	GetCurrentScene()->ForEach([](UIItem* item) { item->Draw(); });

	Renderer::End();
}

void Application::Run()
{
	for (auto& scene : m_Scenes) scene.second->Init();
	Begin();
	while (m_Running)
	{
		Time::Tick();
		Event(&Input::Event());
		Update();
		Draw();
		PerformanceManager::PerformCapping();
	}
}

void Application::AddSceneOnSequencer(const UIString& name)
{
	UIASSERT(IsNameDuplicate(name), "Non-existing name for scene");
	UIASSERT(std::find(m_SceneSequencer.begin(), m_SceneSequencer.end(), name)
		== m_SceneSequencer.end(), "This scene is already sequenced!!");
	m_SceneSequencer.push_back(name);
}

void Application::ChangeScene(const UIString& name)
{
	UIASSERT(IsNameDuplicate(name), "Non-existing name!!");
	m_CurrentScene = m_Scenes.find(name);
}

void Application::ChangeScene(UIUnsignedInt index)
{
	UIASSERT(index < m_SceneSequencer.size(), "SceneSequencer overflow!!");
	m_CurrentScene = m_Scenes.find(m_SceneSequencer.at(index));
}

void Application::NextScene()
{
	auto it = std::find(m_SceneSequencer.begin(), m_SceneSequencer.end(), m_CurrentScene->first);
	UIASSERT(it != m_SceneSequencer.end(), "Current Scene not in sequencer");
	it++;
	if (it == m_SceneSequencer.end())
	{
		m_CurrentScene = m_Scenes.find(m_SceneSequencer.front());
		return;
	}
	m_CurrentScene = m_Scenes.find(*it);
}

void Application::PreviousScene()
{
	auto it = std::find(m_SceneSequencer.begin(), m_SceneSequencer.end(), m_CurrentScene->first);
	UIASSERT(it != m_SceneSequencer.end(), "Current Scene not in sequencer");
	if (it == m_SceneSequencer.begin())
	{
		m_CurrentScene = m_Scenes.find(m_SceneSequencer.back());
		return;
	}
	it--;
	m_CurrentScene = m_Scenes.find(*it);
}

Scene* Application::GetCurrentScene()
{
	return m_CurrentScene->second.get();
}

void Application::PrintHirarchiesOnConsole()
{
	for (auto& scene : m_Scenes)
	{
		scene.second->PrintHierarchyOnConsole();
	}
}

void Application::PrintHirarchiesOnStream(const UIString& filepath)
{
	for (auto& scene : m_Scenes) scene.second->PrintHierarchyOnFile(filepath);
}

Scene* Application::GetScene(const UIString& name)
{
	UIASSERT(IsNameDuplicate(name), "Non-existing name!!");
	return m_Scenes.at(name).get();
}

bool Application::IsNameDuplicate(const UIString& name)
{
	for (auto& [key, value] : m_Scenes)
	{
		if (key == name) return true;
	}

	return false;
}
