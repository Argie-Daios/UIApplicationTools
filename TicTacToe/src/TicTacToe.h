#pragma once

#include <UIApplicationTools.h>

class TicTacToe : public Application
{
public:
	/// <summary>
	/// Initialization of scenes and assets
	/// </summary>
	TicTacToe();
	virtual ~TicTacToe() override;

	/// <summary>
	/// In this function, you put stuff for specific things (DO NOT INITIIALIZE ASSETS HERE)
	/// </summary>
	virtual void Begin() override;
	/// <summary>
	/// In this function, you put stuff to execute every frame
	/// </summary>
	virtual void Update() override;
};