#pragma once

#include <UIApplicationTools.h>

class StartingScene : public Scene
{
public:
	StartingScene() = default;
	StartingScene(const UIString& name);
	virtual ~StartingScene() override;

	virtual void Init() override;
	virtual void Update() override;
private:
	UIInputBox* m_InputBox;
	UIInputBox* m_InputBox2;
	UIButton* m_EnterButton;
	UIButton* m_BackButton;
	UIButton* m_TestButton;
};