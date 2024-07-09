#pragma once

#include "UIItem.h"

#include <functional>

enum class UIButtonMode : UIUnsignedByte
{
	UINormal,
	UIToggle,
	UIFocus
};

class UIBox : public UIItem
{
public:
	UIBox();
	UIBox(const Vector2f& position, const Vector2f& size, const ColorRGBA& color = ColorRGBA(255, 255, 255),
		UIBool visible = true, UIUnsignedInt thickness = 3);
	UIBox(const UIBox& box) = default;
	virtual ~UIBox() override;

	virtual void Draw() override;
private:
	UIUnsignedInt m_Thickness;
};

class UIImage : public UIItem
{
public:
	UIImage();
	UIImage(const Vector2f& position, const Vector2f& size, const ColorRGBA& color = ColorRGBA(255, 255, 255));
	UIImage(const Vector2f& position, const UIString& textureID, const Vector2f& size = Vector2f(-1, -1), 
		const ColorRGBA& color = ColorRGBA(255, 255, 255));
	UIImage(const UIImage& image) = default;
	virtual ~UIImage() override;

	virtual void Draw() override;
};

class UIText : public UIItem
{
public:
	UIText();
	UIText(const Vector2f& position, const UIString& label, const UIString& fontID, const ColorRGBA& color);
	UIText(const UIText& text);
	virtual ~UIText() override;

	virtual void SetColor(const ColorRGBA& color) override;
	void SetLabel(const UIString& label);
	inline UIString GetLabel() const { return m_Label; }
	UIInt GetWidth() const;
	UIInt GetHeight() const;
	ColorRGBA GetColor() const { return m_Mesh.Color; }

	virtual void Draw() override;
private:
	void RefreshTexture();
private:
	UIString m_Label;
	UIString m_FontID;
};

class UIButton : public UIWidget
{
public:
	UIButton();
	UIButton(const Vector2f& position, const Vector2f& size, const UIString& label,
		const ColorRGBA& textColor, const ColorRGBA& backgroundColor);
	UIButton(const Vector2f& position, const Vector2f& size, const UIString& label, const ColorRGBA& textColor);
	UIButton(UIItem* item);
	UIButton(const Vector2f& position, UIItem* item);
	UIButton(const UIButton& button) = delete;
	virtual ~UIButton() override;

	void BindOnExitHoverCallback(const std::function<void(UIButton* self)>& function);
	void BindOnHoverCallback(const std::function<void(UIButton* self)>& function);
	void BindOnClickCallback(const std::function<void(UIButton* self)>& function);
	void BindOnReleaseCallback(const std::function<void(UIButton* self)>& function);

	void UnbindOnExitHoverCallback();
	void UnbindOnHoverCallback();
	void UnbindOnClickCallback();
	void UnbindOnReleaseCallback();
	void UnbindCallbacks();

	inline void SetNeutralColor(const ColorRGBA& color) { m_NeutralColor = color; }
	inline void SetHoveredColor(const ColorRGBA& color) { m_HoveredColor = color; }
	inline void SetActiveColor(const ColorRGBA& color) { m_ActiveColor = color; }
	inline ColorRGBA GetNeutralColor() const { return m_NeutralColor; }
	inline ColorRGBA GetHoveredColor() const { return m_HoveredColor; }
	inline ColorRGBA GetActiveColor() const { return m_ActiveColor; }

	inline void SetMode(UIButtonMode mode) { m_Mode = mode; }
	inline UIButtonMode GetMode() const { return m_Mode; }

	inline UIItem* GetAttachedItem() const { return m_Item; }

	virtual void Update() override;
	virtual void Draw() override;
protected:
	void SetItem(UIItem* item);
private:
	enum class UIButtonState : UIUnsignedByte
	{
		NEUTRAL,
		HOVERED,
		ACTIVE
	};
private:
	void SetColor(const ColorRGBA& color);
	void ManageNormalMode(const SDL_Rect& rect);
	void ManageToggleMode(const SDL_Rect& rect);
	void ManageFocusMode(const SDL_Rect& rect);
private:
	UIItem* m_Item;
	ColorRGBA m_NeutralColor;
	ColorRGBA m_HoveredColor;
	ColorRGBA m_ActiveColor;
	UIButtonMode m_Mode;
	UIButtonState m_State;
	UIBool m_HandleDraw;

	std::function<void(UIButton* self)> OnExitHover;
	std::function<void(UIButton* self)> OnHover;
	std::function<void(UIButton* self)> OnClick;
	std::function<void(UIButton* self)> OnRelease;
};

class UILayerMask : public UIBox
{
public:
	UILayerMask();
	UILayerMask(const Vector2f& position, const Vector2f& size, const ColorRGBA& color = ColorRGBA(255, 255, 255),
		UIBool visible = true, UIUnsignedInt thickness = 3);
	UILayerMask(const UILayerMask& box) = default;
	virtual ~UILayerMask() override;

	virtual void Draw() override;
};