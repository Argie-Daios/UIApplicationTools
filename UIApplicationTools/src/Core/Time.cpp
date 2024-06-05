#include "Time.h"

#include <SDL.h>

UIFloat Time::s_DeltaTime = 0.0f;
UIFloat Time::s_LastFrameTime = 0.0f;

void Time::Init()
{
	
}

void Time::Tick()
{
	UIFloat time = (UIFloat)SDL_GetTicks() / 1000.0f;
	s_DeltaTime = time - s_LastFrameTime;
	s_LastFrameTime = time;
}
