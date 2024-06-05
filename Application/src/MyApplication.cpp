#include "MyApplication.h"

#include "Core/EntryPoint.h"
#include "MainMenu.h"
#include "StartingScene.h"

Application* CreateApplication(int argc, char** argv)
{
	return new MyApplication();
}

MyApplication::MyApplication()
	: Application()
{
	AssetManager::LoadFont("Arial_Regular_40", "assets/Arial.ttf", 40);
	AssetManager::LoadFont("Arial_Regular_60", "assets/Arial.ttf", 60);
	AddScene<MainMenu>("MainMenu");
	AddScene<StartingScene>("StartingScene");
	AddSceneOnSequencer("MainMenu");
	AddSceneOnSequencer("StartingScene");
}

MyApplication::~MyApplication()
{

}

void MyApplication::Begin()
{
	Application::Begin();
	PrintHirarchiesOnConsole();
}

void MyApplication::Update()
{
	Application::Update();
}