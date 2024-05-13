#include "UIElements.h"

#include <Rendering/Renderer.h>

Image::Image()
	: Item(), m_Texture(nullptr), m_Color{ 255,255,255 }
{
	
}

Image::Image(const glm::vec2& position)
	: Item(position), m_Texture(nullptr), m_Color{ 255,255,255 }
{

}

Image::Image(const glm::vec2& position, const std::string& texture_path)
	: Item(position), m_Texture(nullptr), m_Color{ 255,255,255 }
{
	m_Texture = Renderer::CreateTexture(texture_path);
}

Image::~Image()
{
	Renderer::DeleteTexture(m_Texture);
}

void Image::Draw()
{
	if (m_Texture)
	{
		Renderer::DrawTexture(m_Transform, m_Texture);
	}
	else
	{
		Renderer::DrawQuad(m_Transform, glm::ivec2(300, 300), m_Color);
	}
}