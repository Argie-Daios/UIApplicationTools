#include "Game.h"

#include "TicTacToe.h"
#include <algorithm>

Game::Game(const UIString& name)
	: Scene(name)
{

}

Game::~Game()
{

}

void Game::Init()
{
	for (UIInt i = 0; i < GRID_SIZE; i++)
	{
		for (UIInt j = 0; j < GRID_SIZE; j++)
		{
			UIInt index = i * GRID_SIZE + j;
			m_TableState[index] = '-';
		}
	}

	UIItem* background = AddItem<UIImage>("Background", Vector2f(0, 0), "ChalkBoard", Vector2f(TicTacToe::GetWindow()->GetWidth(),
		TicTacToe::GetWindow()->GetHeight()));

	background->SetDepthValue(-1.0f);

	UIItem* line = AddItem<UIImage>("Line", Vector2f(), "ChalkLine", Vector2f(15, 860));
	UIItem* line2 = AddItem<UIImage>("Line2", Vector2f(), "ChalkLine", Vector2f(15, 860));
	UIItem* line3 = m_Line = AddItem<UIImage>("Line3", Vector2f(), "ChalkLine", Vector2f(15, 860));
	UIItem* line4 = AddItem<UIImage>("Line4", Vector2f(), "ChalkLine", Vector2f(15, 860));
	line3->Rotate(90.0f);
	line4->Rotate(90.0f);

	ColorRGBA color = line->GetColor();
	color.a = 150;
	line->SetColor(color);

	UIItem* box = AddItem<UIBox>("BoardPanel", Vector2f(0, 0), Vector2f(780, 780), ColorRGBA(0, 0, 0, 0), false);

	line->Attach(box);
	UIMath::Positioner::PositionItemToParent(line, UIMath::PositioningAreas::UP_LEFT, Vector2f(255, -40));

	line2->Attach(box);
	UIMath::Positioner::PositionItemToParent(line2, UIMath::PositioningAreas::UP_LEFT, Vector2f(515, -40));

	line3->Attach(box);
	UIMath::Positioner::PositionItemToParent(line3, UIMath::PositioningAreas::UP, Vector2f(0, -40 - 125 - 10));

	line4->Attach(box);
	UIMath::Positioner::PositionItemToParent(line4, UIMath::PositioningAreas::UP, Vector2f(0, -40 + 125 + 10 -5));

	for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++)
	{
		UIItem* square9 = AddItem<UIImage>(randomStringGenerator(10), Vector2f(), Vector2f(250, 250), ColorRGBA(255, 255, 255, 0));
		m_Squares.push_back(AddItem<UIButton>(randomStringGenerator(10), Vector2f(), square9));
		UIButton* button = Cast<UIButton*>(m_Squares[i]);
		button->SetNeutralColor(ColorRGBA(255, 255, 255, 0));
		button->SetHoveredColor(ColorRGBA(255, 255, 255, 50));
		button->SetActiveColor(ColorRGBA(255, 255, 255, 100));

		button->BindOnReleaseCallback([&](UIButton* self) {
			Move(self);
		});
		m_Squares[i]->Attach(box);
		UIMath::Positioner::PositionItemToParent(m_Squares[i], (UIMath::PositioningAreas)i);
	}

	UIMath::Positioner::PositionItemToWindow(box, UIMath::PositioningAreas::UP);
}

void Game::Update()
{
	
}

void Game::UpdateGrid(UIInt pickedSquare)
{
	UIItem* pickedItem = m_Squares.at(pickedSquare);
	UIASSERT(pickedItem, "Null item!!");

	// Swap the empty square with the symbol of the current player
	UIItem* image = AddItem<UIImage>(randomStringGenerator(10), pickedItem->GetTransform().position, 
		(m_bPlayerXplays ? "X_image" : "O_image"));
	auto& it = m_Squares.begin() + pickedSquare;
	m_TableState[pickedSquare] = (m_bPlayerXplays ? 'X' : 'O'); // Update the status grid
	it = m_Squares.erase(it);
	m_Squares.insert(it, image);
	RemoveItem(pickedItem);
}

void Game::EndRound()
{
	m_bPlayerXplays = !m_bPlayerXplays;
}

bool Game::CheckWinner()
{
	// Check rows
	for (UIInt i = 0; i < GRID_SIZE; i++)
	{
		UIInt sameSymbols = 0;
		UIChar symbol = m_TableState[i * GRID_SIZE];
		if (symbol == '-') continue;
		for (UIInt j = 0; j < GRID_SIZE; j++)
		{
			UIInt index = i * GRID_SIZE + j;
			if (m_TableState[index] == symbol) sameSymbols++;
		}
		if (sameSymbols == WINNING_SCORE) return true;
	}

	// Check cols
	for (UIInt j = 0; j < GRID_SIZE; j++)
	{
		UIInt sameSymbols = 0;
		UIChar symbol = m_TableState[j];
		if (symbol == '-') continue;
		for (UIInt i = 0; i < GRID_SIZE; i++)
		{
			UIInt index = i * GRID_SIZE + j;
			if (m_TableState[index] == symbol) sameSymbols++;
		}
		if (sameSymbols == WINNING_SCORE) return true;
	}

	// Check 1st Diagonal
	{
		UIInt sameSymbols = 0;
		UIChar symbol = m_TableState[0];
		if (symbol != '-')
		{
			for (UIInt i = 0; i < GRID_SIZE; i++)
			{
				for (UIInt j = 0; j < GRID_SIZE; j++)
				{
					if (i != j) continue;
					UIInt index = i * GRID_SIZE + j;
					if (m_TableState[index] == symbol) sameSymbols++;
				}
			}
			if (sameSymbols == WINNING_SCORE) return true;
		}
	}

	// Check 2nd Diagonal
	{
		UIInt sameSymbols = 0;
		UIChar symbol = m_TableState[GRID_SIZE - 1];
		if (symbol != '-')
		{
			for (UIInt i = 0; i < GRID_SIZE; i++)
			{
				for (UIInt j = 0; j < GRID_SIZE; j++)
				{
					if (i + j != GRID_SIZE - 1) continue;
					UIInt index = i * GRID_SIZE + j;
					if (m_TableState[index] == symbol) sameSymbols++;
				}
			}
			if (sameSymbols == WINNING_SCORE) return true;
		}
	}

	return false;
}

Game::GameState Game::isOver()
{
	if (CheckWinner()) return GameState::WINNER;

	int counter = 0;
	for (int i = 0; i < m_Squares.size(); i++)
	{
		UIButton* testPtr = Cast<UIButton*>(m_Squares.at(i));
		if (testPtr) return GameState::PLAYING;
	}

	return GameState::TIE;
}

void Game::Move(UIButton* self)
{
	auto& it = std::find(m_Squares.begin(), m_Squares.end(), self);
	UIInt index = it - m_Squares.begin();
	UpdateGrid(index);

	GameState state = isOver();
	if (state != GameState::PLAYING)
	{
		if (state == GameState::WINNER)
		{
			std::cout << "Player '" << (m_bPlayerXplays ? 'X' : 'O') << "' won!!" << std::endl;
		}
		else
		{
			std::cout << "Tie!!" << std::endl;
		}
		TicTacToe::Get()->ChangeScene("Menu");
		TicTacToe::Get()->RemoveScene("Game");
	}

	EndRound();
}