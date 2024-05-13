#pragma once

#include <string>

#define SDL_WINDOWPOS_CENTERED_MASK    0x2FFF0000u
#define SDL_WINDOWPOS_CENTERED_DISPLAY(X)  (SDL_WINDOWPOS_CENTERED_MASK|(X))
#define SDL_WINDOWPOS_CENTERED         SDL_WINDOWPOS_CENTERED_DISPLAY(0)

struct SDL_Window;

class Window
{
public:
	/// <summary>
	/// Constructs a Window instance
	/// </summary>
	/// <param name="title: "> The name of the window </param>
	/// <param name="width: "> The width of the window on px </param>
	/// <param name="height: "> The height of the window on px </param>
	/// <param name="posX: "> The initial position on the X axis of the window </param>
	/// <param name="posY: "> The initial position on the Y axis of the window </param>
	/// <param name="flags: "> The window flags for extra functionality </param>
	Window(const std::string& title, int width, int height, int posX = SDL_WINDOWPOS_CENTERED,
		int posY = SDL_WINDOWPOS_CENTERED, unsigned int flags = 0);
	/// <summary>
	/// Destroys this Window instance
	/// </summary>
	~Window();

	/// <summary>
	/// Access to the SDL format of the Window
	/// </summary>
	/// <returns> The SDL formated Window </returns>
	inline SDL_Window* Get() { return m_Window; }

	/// <summary>
	/// Getter for the Window's width
	/// </summary>
	/// <returns> The window's width </returns>
	inline int GetWidth() { return m_Width; }
	/// <summary>
	/// Getter for the Window's height
	/// </summary>
	/// <returns> The window's height </returns>
	inline int GetHeight() { return m_Height; }
private:
	SDL_Window* m_Window;

	int m_Width;
	int m_Height;
};