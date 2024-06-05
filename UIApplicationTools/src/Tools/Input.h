#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"
#include <glm/glm.hpp>

typedef uint8_t Uint8;

class Input
{
public:
	static bool IsKeyPressed(Key key);
	static bool IsKeyDown(Key key);
	static bool IsMouseButtonPressed(Mouse button);
	static bool IsMouseButtonUp(Mouse button);
	static glm::ivec2 GetMousePosition();
	static bool DoesMouseHover(const struct SDL_Rect& rect);

	static union SDL_Event& Event() { return s_Event; }
    static int PollEvent();
private:
	static const Uint8* s_Keystates;
	static SDL_Event s_Event;
};