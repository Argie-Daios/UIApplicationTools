#include "MainMenu.h"

#include "MyApplication.h"

MainMenu::MainMenu(const UIString& name)
	: Scene(name), m_Start(nullptr), m_Settings(nullptr), m_Exit(nullptr)
{
	
}

MainMenu::~MainMenu()
{

}

void MainMenu::Init()
{
	UIItem* startText = AddItem<UIText>("Start_Text", Vector2f(), "Start", "Arial_Regular_60",
		ColorRGBA(255, 255, 255));
	UIItem* settingsText = AddItem<UIText>("Settings_Text", Vector2f(), "Settings", "Arial_Regular_60",
		ColorRGBA(255, 255, 255));
	UIItem* exitText = AddItem<UIText>("Exit_Text", Vector2f(), "Exit", "Arial_Regular_60",
		ColorRGBA(255, 255, 255));

	m_Start = AddItem<UIButton>("Start_Button", Vector2f(), startText, UIButtonType::UIText);
	m_Start->SetNeutralColor(ColorRGBA(255, 255, 255));
	m_Start->SetHoveredColor(ColorRGBA(255, 0, 0));
	m_Start->SetActiveColor(ColorRGBA(190, 0, 0));
	m_Start->BindOnReleaseCallback([&](UIButton* self) {
		MyApplication::Get()->NextScene();
		});

	m_Settings = AddItem<UIButton>("Settings_Button", Vector2f(), settingsText, UIButtonType::UIText);
	m_Settings->SetNeutralColor(ColorRGBA(255, 255, 255));
	m_Settings->SetHoveredColor(ColorRGBA(255, 0, 0));
	m_Settings->SetActiveColor(ColorRGBA(190, 0, 0));

	m_Exit = AddItem<UIButton>("Exit_Button", Vector2f(), exitText, UIButtonType::UIText);
	m_Exit->SetNeutralColor(ColorRGBA(255, 255, 255));
	m_Exit->SetHoveredColor(ColorRGBA(255, 0, 0));
	m_Exit->SetActiveColor(ColorRGBA(190, 0, 0));
	m_Exit->BindOnReleaseCallback([&](UIButton* self) { MyApplication::Get()->Shutdown(); });

	UIMath::Positioner::PositionItemToWindow(m_Start, UIMath::PositioningAreas::CENTER, Vector2f(0, -100));

	UIMath::Positioner::PositionItemToWindow(m_Settings, UIMath::PositioningAreas::CENTER);

	UIMath::Positioner::PositionItemToWindow(m_Exit, UIMath::PositioningAreas::CENTER, Vector2f(0, 100));
}

void MainMenu::Update()
{

}