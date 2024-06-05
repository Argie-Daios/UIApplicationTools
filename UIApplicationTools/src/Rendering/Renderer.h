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

	static void DrawRect(const Transform& transform, const Vector2f& size, const ColorRGBA& color,
		UIUnsignedInt thickness);
	static void DrawQuad(const Transform& transform, const Vector2f& size, const ColorRGBA& color);
	static void DrawTexture(const Transform& transform, const UIString& textureID, const Vector2f& size = Vector2f(-1, -1));
	static void DrawTexture(const Transform& transform, struct UITexture* texture, const Vector2f& size = Vector2f(-1, -1));

	static SDL_Texture* CreateTextureFromSurface(struct SDL_Surface* surface);
private:
	static SDL_Renderer* s_Renderer;
	friend class AssetManager;
};