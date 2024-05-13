#pragma once

#include "Item.h"

#include <string>

class Image : public Item
{
public:
	Image();
	Image(const glm::vec2& position);
	Image(const glm::vec2& position, const std::string& texture_path);
	virtual ~Image() override;

	virtual void Draw() override;
private:
	struct SDL_Texture* m_Texture;
	Color m_Color;
};