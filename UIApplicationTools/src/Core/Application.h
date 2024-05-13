#pragma once

#include "Macros.h"
#include "Rendering/Window.h"
#include "Items/UIElements.h"

class Application
{
public:
	Application();
	~Application();

	virtual void Event(union SDL_Event* event);
	virtual void Update();
	virtual void Draw();
	virtual void Run();

	static void Shutdown() { s_Instance->m_Running = false; }
private:
	static Application* s_Instance;
	static std::shared_ptr<Window> s_Window;
	bool m_Running = true;

	Image m_Image;
};