#pragma once

using UIFloat = float;

class Time
{
public:
	static void Init();
	static void Tick();

	// DeltaTime in seconds
	inline static UIFloat DeltaTime() { return s_DeltaTime; }

	inline static UIFloat SecToMs(UIFloat value) { return value * 1000.0f; }
	inline static UIFloat MsToSec(UIFloat value) { return value / 1000.0f; }
private:
	static UIFloat s_DeltaTime;
	static UIFloat s_LastFrameTime;
};