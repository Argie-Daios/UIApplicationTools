#pragma once

#include <UIApplicationTools.h>

class MainMenu : public Scene
{
public:
	MainMenu() = default;
	MainMenu(const UIString& name);
	virtual ~MainMenu() override;

	virtual void Init() override;
	virtual void Update() override;
private:
	UIButton* m_NewGameButton;
	UIButton* m_ExitButton;
};

