#include "Renderer.h"

#include "Window.h"

#include <SDL.h>
#include <SDL_image.h>

SDL_Renderer* Renderer::s_Renderer = nullptr;

void Renderer::Init(SDL_Window* window)
{
	s_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
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

void Renderer::DrawQuad(const Transform& transform, const glm::vec2& size, const Color& color)
{
	SDL_Rect rect;

	rect.x = transform.position.x;
	rect.y = transform.position.y;
	rect.w = size.x;
	rect.h = size.y;

	Uint8 tempR, tempG, tempB, tempA;
	SDL_GetRenderDrawColor(s_Renderer, &tempR, &tempG, &tempB, &tempA);
	SDL_SetRenderDrawColor(s_Renderer, color.r, color.g, color.b, 255);

	SDL_RenderFillRect(s_Renderer, &rect);

	SDL_SetRenderDrawColor(s_Renderer, tempR, tempG, tempB, tempA);
}

void Renderer::DrawTexture(const Transform& transform, SDL_Texture* texture, const glm::vec2& size)
{
	SDL_Rect src, dst;

	int width, height;
	SDL_QueryTexture(texture, 0, 0, &width, &height);

	src.x = 0;
	src.y = 0;
	dst.x = transform.position.x;
	dst.y = transform.position.y;

	src.w = dst.w = width;
	src.h = dst.h = height;

	SDL_RenderCopyEx(s_Renderer, texture, &src, &dst, transform.rotation, nullptr, SDL_FLIP_NONE);
}

SDL_Texture* Renderer::CreateTexture(const std::string& tex_path)
{
	SDL_Surface* surface = IMG_Load(tex_path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(s_Renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

void Renderer::DeleteTexture(SDL_Texture* texture)
{
	if (texture == nullptr) return;

	SDL_DestroyTexture(texture);
}
