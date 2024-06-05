#include "Renderer.h"

#include "Window.h"
#include "Tools/AssetManager.h"
#include "Core/Macros.h"

#include <SDL.h>
#include <SDL_image.h>

SDL_Renderer* Renderer::s_Renderer = nullptr;

void Renderer::Init(SDL_Window* window)
{
	s_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_SetRenderDrawBlendMode(s_Renderer, SDL_BLENDMODE_BLEND);
}

void Renderer::Shutdown()
{
	SDL_DestroyRenderer(s_Renderer);
}

void Renderer::Begin()
{
	SDL_RenderClear(s_Renderer);
}

void Renderer::End()
{
	SDL_RenderPresent(s_Renderer);
}

void Renderer::DrawRect(const Transform& transform, const Vector2f& size, const ColorRGBA& color, UIUnsignedInt thickness)
{
	UIASSERT(thickness < 100, "Too thick!!");
	SDL_Rect rect;
	rect.x = (UIInt)transform.position.X();
	rect.y = (UIInt)transform.position.Y();
	rect.w = (UIInt)size.X();
	rect.h = (UIInt)size.Y();

	Uint8 tempR, tempG, tempB, tempA;
	SDL_GetRenderDrawColor(s_Renderer, &tempR, &tempG, &tempB, &tempA);
	SDL_SetRenderDrawColor(s_Renderer, color.r, color.g, color.b, color.a);
	for (UIUnsignedInt i = 0; i < thickness; i++)
	{
		SDL_RenderDrawRect(s_Renderer, &rect);
		rect.x++;
		rect.y++;
		rect.w -= 2;
		rect.h -= 2;
	}
	SDL_SetRenderDrawColor(s_Renderer, tempR, tempG, tempB, tempA);
}

void Renderer::DrawQuad(const Transform& transform, const Vector2f& size, const ColorRGBA& color)
{
	SDL_Rect rect;

	rect.x = (UIInt)transform.position.X();
	rect.y = (UIInt)transform.position.Y();
	rect.w = (UIInt)size.X();
	rect.h = (UIInt)size.Y();

	Uint8 tempR, tempG, tempB, tempA;
	SDL_GetRenderDrawColor(s_Renderer, &tempR, &tempG, &tempB, &tempA);
	SDL_SetRenderDrawColor(s_Renderer, color.r, color.g, color.b, color.a);

	SDL_RenderFillRect(s_Renderer, &rect);

	SDL_SetRenderDrawColor(s_Renderer, tempR, tempG, tempB, tempA);
}

void Renderer::DrawTexture(const Transform& transform, const UIString& textureID, const Vector2f& size)
{
	SDL_Rect src, dst;

	int texWidth, texHeight;
	UITexture* texture = AssetManager::ReceiveTexture(textureID);
	SDL_QueryTexture(texture->Texture, 0, 0, &texWidth, &texHeight);

	src.x = 0;
	src.y = 0;
	dst.x = (UIInt)transform.position.X();
	dst.y = (UIInt)transform.position.Y();

	src.w = texWidth;
	src.h = texHeight;
	dst.w = (UIInt)size.X();
	dst.h = (UIInt)size.Y();
	
	SDL_RenderCopyEx(s_Renderer, texture->Texture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
}

void Renderer::DrawTexture(const Transform& transform, UITexture* texture, const Vector2f& size)
{
	SDL_Rect src, dst;

	int texWidth, texHeight;
	SDL_QueryTexture(texture->Texture, 0, 0, &texWidth, &texHeight);

	src.x = 0;
	src.y = 0;
	dst.x = (UIInt)transform.position.X();
	dst.y = (UIInt)transform.position.Y();

	src.w = texWidth;
	src.h = texHeight;
	dst.w = (UIInt)size.X();
	dst.h = (UIInt)size.Y();

	SDL_RenderCopyEx(s_Renderer, texture->Texture, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
}

SDL_Texture* Renderer::CreateTextureFromSurface(SDL_Surface* surface)
{	UIASSERT(surface, "Surface failed to load!!");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(s_Renderer, surface);
	UIASSERT(texture, "Texture failed to load!!");
	return texture;
}
