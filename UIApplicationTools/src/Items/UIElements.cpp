#include "UIElements.h"

#include "Rendering/Renderer.h"
#include "Tools/AssetManager.h"
#include "Core/Macros.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Image::Image()
	: UIItem(), m_TextureID(invalidName)
{

}

Image::Image(const Vector2f& position, const Vector2f& size, const ColorRGB& color)
	: UIItem(position, size), m_TextureID(invalidName), m_Color(color)
{

}

Image::Image(const Vector2f& position, const UIString& textureID, const Vector2f& size)
	: UIItem(position, size), m_TextureID(textureID), m_Color{ 255,255,255 }
{

}

Image::~Image()
{
	
}

void Image::Draw()
{
	if (AssetManager::IsInvalid(m_TextureID))
	{
		Renderer::DrawQuad(m_Transform, m_Size, m_Color);
	}
	else
	{
		Renderer::DrawTexture(m_Transform, m_TextureID, m_Size);
	}
}

Text::Text()
	: UIItem(), m_Texture(nullptr)
{

}

Text::Text(const Vector2f& position, const UIString& label, const UIString& fontID, const ColorRGB& color)
	: UIItem(position), m_Label(label), m_Texture(nullptr), m_FontID(fontID), m_Color(color)
{
	RefreshTexture();
}

Text::Text(const Text& text)
	: m_Label(text.m_Label), m_FontID(text.m_FontID), m_Color(text.m_Color)
{
	RefreshTexture();
}

Text::~Text()
{
	if(m_Texture && m_Texture->Texture) SDL_DestroyTexture(m_Texture->Texture);
}

void Text::Draw()
{
	Renderer::DrawTexture(m_Transform, m_Texture.get());
}

void Text::RefreshTexture()
{
	if (m_Texture == nullptr) m_Texture = CreateUIScopePointer<UITexture>();
	UIFont* font = AssetManager::ReceiveFont(m_FontID);
	SDL_Surface* surface = TTF_RenderText_Solid(font->Font, m_Label.c_str(), m_Color);
	m_Texture->Texture = Renderer::CreateTextureFromSurface(surface);
}