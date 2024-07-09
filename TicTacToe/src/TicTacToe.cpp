#include "TicTacToe.h"
#include "Core/EntryPoint.h"

#include "MainMenu.h"

Application* CreateApplication(int argc, char** argv)
{
	return new TicTacToe();
}

TicTacToe::TicTacToe()
	: Application()
{
	AssetManager::LoadFont("Arial_Regular_40", "assets/fonts/Arial.ttf", 40);
	AssetManager::LoadFont("Arial_Regular_60", "assets/fonts/Arial.ttf", 60);
	AssetManager::LoadTexture("X_image", "assets/textures/X_image.png");
	AssetManager::LoadTexture("O_image", "assets/textures/O_image.png");
	AssetManager::LoadTexture("ChalkBoard", "assets/textures/chalkboard.png");
	AssetManager::LoadTexture("ChalkLine", "assets/textures/chalk_line.png");
	AssetManager::LoadTexture("Bar", "assets/textures/bar.png");

	AddScene<MainMenu>("Menu");
}

TicTacToe::~TicTacToe()
{

}

void TicTacToe::Begin()
{
	Application::Begin();
	PrintHirarchiesOnConsole();
}

void TicTacToe::Update()
{
	Application::Update();
}