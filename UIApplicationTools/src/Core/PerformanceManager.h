#pragma once

using UIUnsignedInt = unsigned int;

enum class FPS_CAPS : UIUnsignedInt
{
	FPS_UNCAPPED = 0,
	FPS_30 = 30,
	FPS_60 = 60,
	FPS_80 = 80,
	FPS_120 = 120,
	FPS_144 = 144,
	FPS_240 = 240
};

class PerformanceManager
{
public:
	static void SetFPSCap(const FPS_CAPS& cap);
	static void PerformCapping();
private:
	static FPS_CAPS m_FPSCap;
};