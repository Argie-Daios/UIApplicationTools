#pragma once

#include "UIItem.h"

class Image : public UIItem
{
public:
	Image();
	Image(const Vector2f& position, const Vector2f& size, const ColorRGB& color);
	Image(const Vector2f& position, const UIString& textureID, const Vector2f& size = Vector2f(-1, -1));
	virtual ~Image() override;

	virtual void Draw() override;
private:
	UIString m_TextureID;
	ColorRGB m_Color;
};

class Text : public UIItem
{
public:
	Text();
	Text(const Vector2f& position, const UIString& label, const UIString& fontID, const ColorRGB& color);
	Text(const Text& text);
	virtual ~Text() override;

	virtual void Draw() override;
private:
	void RefreshTexture();
private:
	UIString m_Label;
	UIScopePointer<struct UITexture> m_Texture;
	UIString m_FontID;
	ColorRGB m_Color;
};