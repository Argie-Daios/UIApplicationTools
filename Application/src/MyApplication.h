#pragma once

#include <UIApplicationTools.h>

class MyApplication : public Application
{
public:
	/// <summary>
	/// Initialization of scenes and assets
	/// </summary>
	MyApplication();
	virtual ~MyApplication() override;

	/// <summary>
	/// In this function, you put stuff for specific things (DO NOT INITIIALIZE ASSETS HERE)
	/// </summary>
	virtual void Begin() override;
	/// <summary>
	/// In this function, you put stuff to execute every frame
	/// </summary>
	virtual void Update() override;
};