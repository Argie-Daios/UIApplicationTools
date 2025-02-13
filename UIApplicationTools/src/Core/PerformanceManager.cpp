#include "PerformanceManager.h"

#include "Time.h"

#include <iostream>
#include <SDL.h>

using UIInt = int;
using UIFloat = float;

FPS_CAPS PerformanceManager::m_FPSCap = FPS_CAPS::FPS_UNCAPPED;

void PerformanceManager::SetFPSCap(const FPS_CAPS& cap)
{
	m_FPSCap = cap;
}

void PerformanceManager::PerformCapping()
{
	if (m_FPSCap == FPS_CAPS::FPS_UNCAPPED) return;

	UIFloat deltaTime = Time::SecToMs(Time::DeltaTime());
	UIFloat frameDelay = 1000.0f / (UIUnsignedInt)m_FPSCap;
	if(frameDelay > deltaTime)
		SDL_Delay(Uint32(frameDelay - deltaTime));
}