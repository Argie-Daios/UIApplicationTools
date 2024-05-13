#pragma once

#include <string>
#include "Math/Structs.h"

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;

class Renderer
{
public:
	/// <summary>
	/// Initializes the Renderer
	/// </summary>
	/// <param name="window: "> The target window that the Renderer will perform the rendering </param>
	static void Init(SDL_Window* window);
	/// <summary>
	/// Destroys the Renderer
	/// </summary>
	static void Shutdown();

	/// <summary>
	/// Clears the renderer from whatever it rendered (presented) before
	/// </summary>
	static void Begin();
	/// <summary>
	/// Draws all the rendering requests that had been given to the Renderer
	/// </summary>
	static void End();

	static void DrawQuad(const Transform& transform, const glm::vec2& size, const Color& color);
	static void DrawTexture(const Transform& transform, SDL_Texture* texture, const glm::vec2& size = glm::vec2(-1, -1));

	static SDL_Texture* CreateTexture(const std::string& tex_path);
	static void DeleteTexture(struct SDL_Texture* texture);

private:
	static SDL_Renderer* s_Renderer;
};