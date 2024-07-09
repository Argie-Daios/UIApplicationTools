#pragma once

#include <UIApplicationTools.h>

#define GRID_SIZE 3
#define WINNING_SCORE 3

class Game : public Scene
{
public:
	Game() = default;
	Game(const UIString& name);
	virtual ~Game() override;

	virtual void Init() override;
	virtual void Update() override;
private:
	enum class GameState : UIUnsignedByte
	{
		PLAYING,
		TIE,
		WINNER
	};
private:
	void UpdateGrid(UIInt pickedSquare);
	void EndRound();
	bool CheckWinner();
	GameState isOver();
	void Move(UIButton* self);
private:
	UIVector<UIItem*> m_Squares;
	UIChar m_TableState[GRID_SIZE * GRID_SIZE];
	UIBool m_bPlayerXplays = true;
	UIItem* m_Line;
};