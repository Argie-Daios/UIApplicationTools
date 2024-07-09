#include "UIElements.h"

#include "Rendering/Renderer.h"
#include "Tools/AssetManager.h"
#include "Core/Macros.h"
#include "Tools/Input.h"
#include "Core/Time.h"
#include "Tools/Logger.h"
#include "Math/Positioner.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// ==== Box ====

UIBox::UIBox()
	: UIItem(), m_Thickness(3)
{

}

UIBox::UIBox(const Vector2f& position, const Vector2f& size, const ColorRGBA& color, UIBool visible,
	UIUnsignedInt thickness)
	: UIItem(position, size, {nullptr, color}), m_Thickness(thickness)
{
	SetActive(visible);
}

UIBox::~UIBox()
{

}

void UIBox::Draw()
{
	if (!m_Active) return;
	Renderer::DrawRect(m_Transform, m_Size, m_Mesh.Color, m_Thickness);
}

// ==== Image ====

UIImage::UIImage()
	: UIItem()
{

}

UIImage::UIImage(const Vector2f& position, const Vector2f& size, const ColorRGBA& color)
	: UIItem(position, size, {nullptr, color})
{

}

UIImage::UIImage(const Vector2f& position, const UIString& textureID, const Vector2f& size, const ColorRGBA& color)
	: UIItem(position, size, {nullptr, color})
{
	UITexture* texture = AssetManager::ReceiveTexture(textureID);
	AddMesh({ texture, color });
	if (size == Vector2f(-1, -1))
	{
		m_Size = Vector2f((UIFloat)texture->Width, (UIFloat)texture->Height);
	}
	else
	{
		m_Size = size;
	}
}

UIImage::~UIImage()
{
	
}

void UIImage::Draw()
{
	if (!m_Active) return;
	if (!m_Mesh.Texture)
	{
		Renderer::DrawQuad(m_Transform, m_Size, m_Mesh.Color);
	}
	else
	{
		Renderer::DrawTexture(m_Transform, m_Mesh.Texture, m_Mesh.Color, m_Size);
	}
}

// ==== Text ====

UIText::UIText()
	: UIItem()
{

}

UIText::UIText(const Vector2f& position, const UIString& label, const UIString& fontID, const ColorRGBA& color)
	: UIItem(position), m_Label(label), m_FontID(fontID)
{
	RefreshTexture();
}

UIText::UIText(const UIText& text)
	: m_Label(text.m_Label), m_FontID(text.m_FontID)
{
	RefreshTexture();
}

UIText::~UIText()
{
	if(m_Mesh.Texture && m_Mesh.Texture->Texture) SDL_DestroyTexture(m_Mesh.Texture->Texture);
	delete m_Mesh.Texture;
}

void UIText::SetColor(const ColorRGBA& color)
{
	m_Mesh.Color = color;
	RefreshTexture();
}

void UIText::SetLabel(const UIString& label)
{
	m_Label = label;
	if (label.empty())
	{
		m_Mesh.Texture->Texture = nullptr;
		return;
	}
	RefreshTexture();
}

UIInt UIText::GetWidth() const
{
	return m_Mesh.Texture->Width;
}

UIInt UIText::GetHeight() const
{
	return m_Mesh.Texture->Height;
}

void UIText::Draw()
{
	if (!m_Active) return;
	if (m_Mesh.Texture->Texture == nullptr) return;
	Renderer::DrawTexture(m_Transform, m_Mesh.Texture, m_Mesh.Color, m_Size);
}

void UIText::RefreshTexture()
{
	if (m_Mesh.Texture == nullptr) m_Mesh.Texture = new UITexture;
	UIFont* font = AssetManager::ReceiveFont(m_FontID);
	SDL_Surface* surface = TTF_RenderText_Solid(font->Font, m_Label.c_str(), m_Mesh.Color);
	m_Mesh.Texture->Texture = Renderer::CreateTextureFromSurface(surface);
	SDL_QueryTexture(m_Mesh.Texture->Texture, 0, 0, &m_Mesh.Texture->Width, &m_Mesh.Texture->Height);
	m_Size = Vector2f((UIFloat)m_Mesh.Texture->Width, (UIFloat)m_Mesh.Texture->Height);
}

// ==== Button ====

UIButton::UIButton()
	: UIWidget(), m_Item(nullptr), m_NeutralColor(255, 255, 255), m_HoveredColor(255, 255, 255),
	m_ActiveColor(255, 255, 255), m_Mode(UIButtonMode::UINormal), m_State(UIButtonState::NEUTRAL),
	m_HandleDraw(false), OnClick(nullptr), OnRelease(nullptr)
{

}

UIButton::UIButton(const Vector2f& position, const Vector2f& size, const UIString& label,
	const ColorRGBA& textColor, const ColorRGBA& backgroundColor)
	: UIWidget(position, size), m_Item(nullptr), m_NeutralColor(backgroundColor), m_HoveredColor(backgroundColor),
	m_ActiveColor(backgroundColor), m_Mode(UIButtonMode::UINormal), m_State(UIButtonState::NEUTRAL),
	m_HandleDraw(true), OnClick(nullptr), OnRelease(nullptr)
{
	UIImage* image = new UIImage(position, size, backgroundColor);
	UIText* text = new UIText(position, label, "Arial_Regular_40", textColor);
	text->Attach(image);
	UIMath::Positioner::PositionItemToParent(text, UIMath::PositioningAreas::CENTER);
	SetItem(image);
}

UIButton::UIButton(const Vector2f& position, const Vector2f& size, const UIString& label,
	const ColorRGBA& textColor)
	: UIWidget(position, size), m_Item(nullptr), m_NeutralColor(textColor), m_HoveredColor(textColor),
	m_ActiveColor(textColor), m_Mode(UIButtonMode::UINormal), m_State(UIButtonState::NEUTRAL),
	m_HandleDraw(true), OnClick(nullptr), OnRelease(nullptr)
{
	UIText* text = new UIText(position, label, "Arial_Regular_40", textColor);
	SetItem(text);
}

UIButton::UIButton(UIItem* item)
	: UIWidget(), m_Item(item), m_NeutralColor(255, 255, 255), m_HoveredColor(255, 255, 255),
	m_ActiveColor(255, 255, 255), m_Mode(UIButtonMode::UINormal), m_State(UIButtonState::NEUTRAL),
	m_HandleDraw(false), OnClick(nullptr), OnRelease(nullptr)
{
	SetItem(item);
}

UIButton::UIButton(const Vector2f& position, UIItem* item)
	: UIWidget(position), m_Item(item), m_NeutralColor(255, 255, 255), m_HoveredColor(255, 255, 255),
	m_ActiveColor(255, 255, 255), m_Mode(UIButtonMode::UINormal), m_State(UIButtonState::NEUTRAL),
	m_HandleDraw(false), OnClick(nullptr), OnRelease(nullptr)
{
	SetItem(item);
}

UIButton::~UIButton()
{
	if (m_HandleDraw)
	{
		for (auto& child : m_Item->GetChildren())
		{
			delete child;
			// If i add more hirearchy depth to button elements i need to refactor
		}
		delete m_Item;
	}
}

void UIButton::BindOnExitHoverCallback(const std::function<void(UIButton* self)>& function)
{
	OnExitHover = function;
}

void UIButton::BindOnHoverCallback(const std::function<void(UIButton* self)>& function)
{
	OnHover = function;
}

void UIButton::BindOnClickCallback(const std::function<void(UIButton* self)>& function)
{
	OnClick = function;
}

void UIButton::BindOnReleaseCallback(const std::function<void(UIButton* self)>& function)
{
	OnRelease = function;
}

void UIButton::UnbindOnExitHoverCallback()
{
	OnExitHover = nullptr;
}

void UIButton::UnbindOnHoverCallback()
{
	OnHover = nullptr;
}

void UIButton::UnbindOnClickCallback()
{
	OnClick = nullptr;
}

void UIButton::UnbindOnReleaseCallback()
{
	OnRelease = nullptr;
}

void UIButton::UnbindCallbacks()
{
	UnbindOnExitHoverCallback();
	UnbindOnHoverCallback();
	UnbindOnClickCallback();
	UnbindOnReleaseCallback();
}

void UIButton::SetItem(UIItem* item)
{
	UIASSERT(item, "Null item!!");
	// Memory leak if used more than once per object
	DettachChildren();
	item->Attach(this);
	item->SetPosition(this->m_Transform.position);
	m_Item = item;

	SetNeutralColor(m_Item->GetColor());

	if (m_Item->GetSize() == Vector2f(-1, -1))
	{
		m_Size = Vector2f((UIFloat)m_Mesh.Texture->Width, (UIFloat)m_Mesh.Texture->Height);
	}
	else
	{
		m_Size = m_Item->GetSize();
	}
}

void UIButton::Update()
{
	if (!m_Active) return;

	glm::ivec2 mousePos = Input::GetMousePosition();
	SDL_Rect itemRect = {
		(int)m_Transform.position.X(),
		(int)m_Transform.position.Y(),
		(int)m_Size.X(),
		(int)m_Size.Y(),
	};

	switch (m_Mode)
	{
	case UIButtonMode::UINormal:
	{
		ManageNormalMode(itemRect);
		break;
	}
	case UIButtonMode::UIToggle:
	{
		ManageToggleMode(itemRect);
		break;
	}
	case UIButtonMode::UIFocus:
	{
		ManageFocusMode(itemRect);
		break;
	}
	}
}

void UIButton::Draw()
{
	if (!m_Active) return;

	if (m_HandleDraw)
	{
		ForEachOnFamilyTree([](UIItem* item) {
			item->Draw();
		});
	}
}

void UIButton::SetColor(const ColorRGBA& color)
{
	UIASSERT(m_Item, "Null item!!");
	m_Item->SetColor(color);
}

void UIButton::ManageNormalMode(const SDL_Rect& rect)
{
	if (m_State == UIButtonState::NEUTRAL && Input::IsMouseButtonPressed(Mouse::Left)) return;

	if (m_State == UIButtonState::HOVERED && Input::IsMouseButtonPressed(Mouse::Left))
	{
		m_State = UIButtonState::ACTIVE;
		SetColor(m_ActiveColor);
		if (OnClick != nullptr) OnClick(this);
	}
	else if (m_State == UIButtonState::ACTIVE && Input::IsMouseButtonUp(Mouse::Left))
	{
		m_State = UIButtonState::HOVERED;
		SetColor(m_HoveredColor);
		if (OnRelease != nullptr) OnRelease(this);
	}
	else if (m_State != UIButtonState::ACTIVE)
	{
		if (Input::DoesMouseHover(rect) && m_State != UIButtonState::HOVERED)
		{
			m_State = UIButtonState::HOVERED;
			SetColor(m_HoveredColor);
			if (OnHover != nullptr) OnHover(this);
		}
		else if (!Input::DoesMouseHover(rect) && m_State != UIButtonState::NEUTRAL)
		{
			m_State = UIButtonState::NEUTRAL;
			SetColor(m_NeutralColor);
			if (OnExitHover != nullptr) OnExitHover(this);
		}
	}
}

void UIButton::ManageToggleMode(const SDL_Rect& rect)
{
	if (m_State == UIButtonState::HOVERED && Input::IsMouseButtonUp(Mouse::Left))
	{
		m_State = UIButtonState::ACTIVE;
		SetColor(m_ActiveColor);
		if (OnClick != nullptr) OnClick(this);
	}
	else if (m_State == UIButtonState::ACTIVE && Input::IsMouseButtonUp(Mouse::Left))
	{
		m_State = UIButtonState::HOVERED;
		SetColor(m_HoveredColor);
		if (OnRelease != nullptr) OnRelease(this);
	}
	else if (m_State != UIButtonState::ACTIVE)
	{
		if (Input::DoesMouseHover(rect) && m_State != UIButtonState::HOVERED)
		{
			m_State = UIButtonState::HOVERED;
			SetColor(m_HoveredColor);
			if (OnHover != nullptr) OnHover(this);
		}
		else if (!Input::DoesMouseHover(rect) && m_State != UIButtonState::NEUTRAL)
		{
			m_State = UIButtonState::NEUTRAL;
			SetColor(m_NeutralColor);
			if (OnExitHover != nullptr) OnExitHover(this);
		}
	}
}

void UIButton::ManageFocusMode(const SDL_Rect& rect)
{
	if (m_State == UIButtonState::HOVERED && Input::IsMouseButtonUp(Mouse::Left))
	{
		m_State = UIButtonState::ACTIVE;
		SetColor(m_ActiveColor);
		if (OnClick != nullptr) OnClick(this);
	}
	else if (m_State == UIButtonState::ACTIVE && !Input::DoesMouseHover(rect) &&
		Input::IsMouseButtonUp(Mouse::Left))
	{
		m_State = UIButtonState::NEUTRAL;
		SetColor(m_NeutralColor);
		if (OnRelease != nullptr) OnRelease(this);
	}
	else if (m_State != UIButtonState::ACTIVE)
	{
		if (Input::DoesMouseHover(rect) && m_State != UIButtonState::HOVERED)
		{
			m_State = UIButtonState::HOVERED;
			SetColor(m_HoveredColor);
			if (OnHover != nullptr) OnHover(this);
		}
		else if (!Input::DoesMouseHover(rect) && m_State != UIButtonState::NEUTRAL)
		{
			m_State = UIButtonState::NEUTRAL;
			SetColor(m_NeutralColor);
			if (OnExitHover != nullptr) OnExitHover(this);
		}
	}
}

UILayerMask::UILayerMask()
	: UIBox()
{

}

UILayerMask::UILayerMask(const Vector2f& position, const Vector2f& size, const ColorRGBA& color, UIBool visible,
	UIUnsignedInt thickness)
	: UIBox(position, size, color, visible, thickness)
{

}

UILayerMask::~UILayerMask()
{

}

void UILayerMask::Draw()
{
	// Crop any successor's mesh if needed
	ForEachOnFamilyTree([this](UIItem* item) {
		Vector2f maskPosition = this->GetTransform().position;
		Vector2f maskSize = this->GetSize();

		// Check if the current item's mesh is out of the bounds of the mask
	});
}
