#include "MainMenu.h"

#include "TicTacToe.h"
#include "Game.h"

MainMenu::MainMenu(const UIString& name)
	: Scene(name)
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::Init()
{
	m_NewGameButton = AddItem<UIButton>("NewGame", Vector2f(), Vector2f(200, 50), "New Game", ColorRGBA(255, 255, 255));
	m_NewGameButton->SetHoveredColor(ColorRGBA(255, 0, 0));
	m_NewGameButton->SetActiveColor(ColorRGBA(200, 0, 0));
	m_NewGameButton->BindOnReleaseCallback([&](UIButton* self) {
		Scene* scene = TicTacToe::Get()->AddScene<Game>("Game");
		scene->Init();
		TicTacToe::Get()->ChangeScene("Game");
	});

	m_ExitButton = AddItem<UIButton>("Exit", Vector2f(), Vector2f(200, 50), "Exit", ColorRGBA(255, 255, 255));
	m_ExitButton->SetHoveredColor(ColorRGBA(255, 0, 0));
	m_ExitButton->SetActiveColor(ColorRGBA(200, 0, 0));
	m_ExitButton->BindOnReleaseCallback([&](UIButton* self) {
		TicTacToe::Get()->Shutdown();
	});

	UIMath::Positioner::PositionItemToWindow(m_NewGameButton, UIMath::PositioningAreas::CENTER, Vector2f(0, -50));
	UIMath::Positioner::PositionItemToWindow(m_ExitButton, UIMath::PositioningAreas::CENTER, Vector2f(0, 50));
}

void MainMenu::Update()
{

}