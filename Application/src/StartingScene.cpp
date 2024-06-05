#include "StartingScene.h"

#include "MyApplication.h"

StartingScene::StartingScene(const UIString& name)
	: Scene(name), m_InputBox(nullptr), m_EnterButton(nullptr), m_BackButton(nullptr)
{

}

StartingScene::~StartingScene()
{

}

void StartingScene::Init()
{
	m_InputBox = AddItem<UIInputBox>("Input_Box", Vector2f(), Vector2f(300, 50));
	UIMath::Positioner::PositionItemToWindow(m_InputBox, UIMath::PositioningAreas::CENTER);

	m_InputBox2 = AddItem<UIInputBox>("Input_Box2", Vector2f(), Vector2f(300, 50));
	UIMath::Positioner::PositionItemToWindow(m_InputBox2, UIMath::PositioningAreas::CENTER, Vector2f(0, 300));

	{
		UIItem* image = AddItem<UIImage>("EnterButton_Background", Vector2f(), Vector2f(150, 50));
		UIItem* text = AddItem<UIText>("EnterButton_Text", Vector2f(), "Enter", "Arial_Regular_40",
			ColorRGBA(0, 0, 0));
		text->Attach(image);
		UIMath::Positioner::PositionItemToParent(text, UIMath::PositioningAreas::CENTER);

		m_EnterButton = AddItem<UIButton>("EnterButton", Vector2f(), image, UIButtonType::UIImage);
		m_EnterButton->SetNeutralColor(ColorRGBA(255, 255, 255));
		m_EnterButton->SetHoveredColor(ColorRGBA(200, 200, 200));
		m_EnterButton->SetActiveColor(ColorRGBA(150, 150, 150));
		UIMath::Positioner::PositionItemToWindow(m_EnterButton, UIMath::PositioningAreas::CENTER,
			Vector2f(250, 0));
		m_EnterButton->BindOnReleaseCallback([&](UIButton* self) {
			m_InputBox->Clear();
			});
	}

	{
		UIItem* image = AddItem<UIImage>("BackButton_Background", Vector2f(), Vector2f(150, 50));
		UIItem* text = AddItem<UIText>("BackButton_Text", Vector2f(), "Back", "Arial_Regular_40",
			ColorRGBA(0, 0, 0));
		text->Attach(image);
		UIMath::Positioner::PositionItemToParent(text, UIMath::PositioningAreas::CENTER);

		m_BackButton = AddItem<UIButton>("BackButton", Vector2f(), image, UIButtonType::UIImage);
		m_BackButton->SetNeutralColor(ColorRGBA(255, 255, 255));
		m_BackButton->SetHoveredColor(ColorRGBA(200, 200, 200));
		m_BackButton->SetActiveColor(ColorRGBA(150, 150, 150));
		UIMath::Positioner::PositionItemToWindow(m_BackButton, UIMath::PositioningAreas::UP_RIGHT,
			Vector2f(-50, 50));
		m_BackButton->BindOnReleaseCallback([&](UIButton* self) {
			MyApplication::Get()->PreviousScene();
			});
	}

	{
		UIItem* image = AddItem<UIImage>("TestButton_Background", Vector2f(), Vector2f(150, 50));
		UIItem* text = AddItem<UIText>("TestButton_Text", Vector2f(), "Test", "Arial_Regular_40",
			ColorRGBA(0, 0, 0));
		text->Attach(image);
		UIMath::Positioner::PositionItemToParent(text, UIMath::PositioningAreas::CENTER);

		m_TestButton = AddItem<UIButton>("TestButton", Vector2f(), image, UIButtonType::UIImage);
		m_TestButton->SetMode(UIButtonMode::UIFocus);
		m_TestButton->SetNeutralColor(ColorRGBA(255, 255, 255));
		m_TestButton->SetHoveredColor(ColorRGBA(200, 200, 200));
		m_TestButton->SetActiveColor(ColorRGBA(150, 150, 150));
		UIMath::Positioner::PositionItemToWindow(m_TestButton, UIMath::PositioningAreas::DOWN_RIGHT,
			Vector2f(-50, -50));

		m_TestButton->BindOnExitHoverCallback([&](UIButton* self) {
			std::cout << "OnExitHover" << std::endl;
			});

		m_TestButton->BindOnHoverCallback([&](UIButton* self) {
			std::cout << "OnHover" << std::endl;
			});

		m_TestButton->BindOnClickCallback([&](UIButton* self) {
			std::cout << "OnClick" << std::endl;
			});

		m_TestButton->BindOnReleaseCallback([&](UIButton* self) {
			std::cout << "OnRelease" << std::endl;
			});
	}
}

void StartingScene::Update()
{

}
