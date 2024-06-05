#pragma once

#include "Macros.h"
#include "UIDefinitions.h"
#include "Rendering/Window.h"
#include "Items/UIElements.h"
#include "Scene.h"

class Application
{
public:
	Application();
	virtual ~Application();

	virtual void Event(union SDL_Event* event);
	virtual void Begin();
	virtual void Update();
	void Draw();
	virtual void Run();
	void Shutdown() { m_Running = false; }

	inline static Application* Get() { return s_Instance; }
	inline static Window* GetWindow() { return s_Window.get(); }

	template<typename T>
	void AddScene(const UIString& name)
	{
		UIASSERT(!IsNameDuplicate(name), "Duplicate name!!");
		m_Scenes.emplace(name, CreateUIReferencePointer<T>(name));
		if (m_Scenes.size() == 1)
		{
			m_CurrentScene = m_Scenes.begin();
		}
	}
	void AddSceneOnSequencer(const UIString& name);
	void ChangeScene(const UIString& name);
	void ChangeScene(UIUnsignedInt index);
	void NextScene();
	void PreviousScene();
	Scene* GetCurrentScene();
protected:
	void PrintHirarchiesOnConsole();
	void PrintHirarchiesOnStream(const UIString& filepath);
private:
	bool IsNameDuplicate(const UIString& name);
	Scene* GetScene(const UIString& name);
private:
	static Application* s_Instance;
	static UIReferencePointer<Window> s_Window;
	bool m_Running = true;

	UIItem* m_InputBox = nullptr;

	// Maybe need change from iterator to Scene* or UIReferencedPointer<Scene>, no need to store an iterator
	UIHashMap<UIString, UIReferencePointer<Scene>>::iterator m_CurrentScene;
	UIHashMap<UIString, UIReferencePointer<Scene>> m_Scenes;
	UIVector<UIString> m_SceneSequencer;
};

Application* CreateApplication(int argc, char** argv);