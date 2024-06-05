#include "UIElements.h"

#include "Rendering/Renderer.h"
#include "Tools/AssetManager.h"
#include "Core/Macros.h"
#include "Tools/Input.h"
#include "Core/Time.h"
#include "Tools/Logger.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// ==== Box ====

UIBox::UIBox()
	: UIItem(), m_Color(255, 255, 255), m_Thickness(3)
{

}

UIBox::UIBox(const Vector2f& position, const Vector2f& size, const ColorRGBA& color, UIBool visible,
	UIUnsignedInt thickness)
	: UIItem(position, size), m_Color(color), m_Thickness(thickness)
{
	SetActive(visible);
}

UIBox::~UIBox()
{

}

void UIBox::Draw()
{
	if (!m_Active) return;
	Renderer::DrawRect(m_Transform, m_Size, m_Color, m_Thickness);
}

// ==== Image ====

UIImage::UIImage()
	: UIItem(), m_TextureID(invalidName), m_Color(255, 255, 255)
{

}

UIImage::UIImage(const Vector2f& position, const Vector2f& size, const ColorRGBA& color)
	: UIItem(position, size), m_TextureID(invalidName), m_Color(color)
{

}

UIImage::UIImage(const Vector2f& position, const UIString& textureID, const Vector2f& size, const ColorRGBA& color)
	: UIItem(position, size), m_TextureID(textureID), m_Color(color)
{
	if (size == Vector2f(-1, -1))
	{
		UITexture* texture = AssetManager::ReceiveTexture(textureID);
		m_Size = Vector2f((UIFloat)texture->Width, (UIFloat)texture->Height);
	}
	else
	{
		m_Size = size;
	}
	std::cout << "m_Size : [" << m_Size.X() << "," << m_Size.Y() << "]\n";
}

UIImage::~UIImage()
{
	
}

void UIImage::Draw()
{
	if (!m_Active) return;
	if (AssetManager::IsInvalid(m_TextureID))
	{
		Renderer::DrawQuad(m_Transform, m_Size, m_Color);
	}
	else
	{
		Renderer::DrawTexture(m_Transform, m_TextureID, m_Size);
	}
}

// ==== Text ====

UIText::UIText()
	: UIItem(), m_Texture(nullptr), m_Color(255, 255, 255)
{

}

UIText::UIText(const Vector2f& position, const UIString& label, const UIString& fontID, const ColorRGBA& color)
	: UIItem(position), m_Label(label), m_Texture(nullptr), m_FontID(fontID), m_Color(color)
{
	RefreshTexture();
}

UIText::UIText(const UIText& text)
	: m_Label(text.m_Label), m_FontID(text.m_FontID), m_Color(text.m_Color)
{
	RefreshTexture();
}

UIText::~UIText()
{
	if(m_Texture && m_Texture->Texture) SDL_DestroyTexture(m_Texture->Texture);
}

void UIText::SetColor(const ColorRGBA& color)
{
	m_Color = color;
	RefreshTexture();
}

void UIText::SetLabel(const UIString& label)
{
	m_Label = label;
	if (label.empty())
	{
		m_Texture->Texture = nullptr;
		return;
	}
	RefreshTexture();
}

UIInt UIText::GetWidth() const
{
	return m_Texture->Width;
}

UIInt UIText::GetHeight() const
{
	return m_Texture->Height;
}

void UIText::Draw()
{
	if (!m_Active) return;
	if (m_Texture->Texture == nullptr) return;
	Renderer::DrawTexture(m_Transform, m_Texture.get(), m_Size);
}

void UIText::RefreshTexture()
{
	if (m_Texture == nullptr) m_Texture = CreateUIScopePointer<UITexture>();
	UIFont* font = AssetManager::ReceiveFont(m_FontID);
	SDL_Surface* surface = TTF_RenderText_Solid(font->Font, m_Label.c_str(), m_Color);
	m_Texture->Texture = Renderer::CreateTextureFromSurface(surface);
	SDL_QueryTexture(m_Texture->Texture, 0, 0, &m_Texture->Width, &m_Texture->Height);
	m_Size = Vector2f((UIFloat)m_Texture->Width, (UIFloat)m_Texture->Height);
}

// ==== Button ====

UIButton::UIButton()
	: UIWidget(), m_Item(nullptr), m_NeutralColor(255, 255, 255), m_HoveredColor(255, 255, 255),
	m_ActiveColor(255, 255, 255), m_Mode(UIButtonMode::UINormal), m_State(UIButtonState::NEUTRAL), m_Type(),
	OnClick(nullptr), OnRelease(nullptr)
{

}

UIButton::UIButton(UIItem* item,  const UIButtonType& type)
	: UIWidget(), m_Item(item), m_NeutralColor(255, 255, 255), m_HoveredColor(255, 255, 255),
	m_ActiveColor(255, 255, 255), m_Mode(UIButtonMode::UINormal), m_State(UIButtonState::NEUTRAL),
	m_Type(type), OnClick(nullptr), OnRelease(nullptr)
{
	UIASSERT(item, "Null item!!");
	item->Attach(this);
	item->SetPosition(this->m_Transform.position);
	if (m_Type == UIButtonType::UIImage)
	{
		UIImage* image = Cast<UIImage*>(m_Item);
		UIASSERT(image, "Failed cast!!");
		image->SetColor(m_NeutralColor);
		
		if (m_Item->GetSize() == Vector2f(-1, -1))
		{
			UITexture* texture = AssetManager::ReceiveTexture(image->GetTextureID());
			m_Size = Vector2f((UIFloat)texture->Width, (UIFloat)texture->Height);
		}
		else
		{
			m_Size = image->GetSize();
		}
	}
	else
	{
		UIText* text = Cast<UIText*>(m_Item);
		UIASSERT(text, "Failed cast!!");
		text->SetColor(m_NeutralColor);

		if (m_Item->GetSize() == Vector2f(-1, -1))
		{
			m_Size = Vector2f((UIFloat)text->GetWidth(), (UIFloat)text->GetHeight());
		}
		else
		{
			m_Size = text->GetSize();
		}
	}
}

UIButton::UIButton(const Vector2f& position, UIItem* item, const UIButtonType& type)
	: UIWidget(position), m_Item(item), m_NeutralColor(255, 255, 255), m_HoveredColor(255, 255, 255),
	m_ActiveColor(255, 255, 255), m_Mode(UIButtonMode::UINormal), m_State(UIButtonState::NEUTRAL)
	, m_Type(type), OnClick(nullptr), OnRelease(nullptr)
{
	UIASSERT(item, "Null item!!");
	item->Attach(this);
	item->SetPosition(position);
	if (m_Type == UIButtonType::UIImage)
	{
		UIImage* image = Cast<UIImage*>(m_Item);
		UIASSERT(image, "Failed cast!!");
		image->SetColor(m_NeutralColor);

		if (m_Item->GetSize() == Vector2f(-1, -1))
		{
			UITexture* texture = AssetManager::ReceiveTexture(image->GetTextureID());
			m_Size = Vector2f((UIFloat)texture->Width, (UIFloat)texture->Height);
		}
		else
		{
			m_Size = image->GetSize();
		}
	}
	else if (m_Type == UIButtonType::UIText)
	{
		UIText* text = Cast<UIText*>(m_Item);
		UIASSERT(text, "Failed cast!!");
		text->SetColor(m_NeutralColor);

		if (m_Item->GetSize() == Vector2f(-1, -1))
		{
			m_Size = Vector2f((UIFloat)text->GetWidth(), (UIFloat)text->GetHeight());
		}
		else
		{
			m_Size = text->GetSize();
		}
	}
}

UIButton::~UIButton()
{

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

void UIButton::Update()
{
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
}

void UIButton::SetColor(const ColorRGBA& color)
{
	if (m_Type == UIButtonType::UIImage)
	{
		UIImage* image = Cast<UIImage*>(m_Item);
		UIASSERT(image, "Failed cast!!");
		image->SetColor(color);
	}
	else if (m_Type == UIButtonType::UIText)
	{
		UIText* text = Cast<UIText*>(m_Item);
		UIASSERT(text, "Failed cast!!");
		text->SetColor(color);
	}
}

void UIButton::ManageNormalMode(const SDL_Rect& rect)
{
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

UIInputBox::UIInputBox()
	: UIWidget(), m_Box(nullptr), m_Text(nullptr), m_Button(nullptr), m_Active(false), m_CursorActive(false)
{
}

UIInputBox::UIInputBox(const Vector2f& position, const Vector2f& size)
	: UIWidget(position, size), m_Active(false), m_CursorActive(false),
	m_Box(CreateUIScopePointer<UIImage>(position, size, ColorRGBA(255, 255, 255))),
	m_Text(CreateUIScopePointer<UIText>(position, "|", "Arial_Regular_40", ColorRGBA(0, 0, 0)))
{
	m_Text->Attach(m_Box.get());
	m_Button = CreateUIScopePointer<UIButton>(position, m_Box.get(), UIButtonType::UIImage);
	m_Button->Attach(this);
	m_Button->BindOnClickCallback([&](UIButton* self) {
		m_Active = true;
		SDL_StartTextInput();
		Logger::DebugMessage("Click", ' ');
	});
	m_Button->BindOnReleaseCallback([&](UIButton* self) {
		m_Active = false;
		SDL_StopTextInput();
		Logger::DebugMessage("Release", ' ');
	});
	m_Button->SetMode(UIButtonMode::UIFocus);
}

UIInputBox::~UIInputBox()
{
	
}

void UIInputBox::Draw()
{
	m_Box->Draw();
	m_Text->Draw();
}

void UIInputBox::Update()
{
	glm::ivec2 mousePos = Input::GetMousePosition();
	SDL_Rect itemRect = {
		(int)m_Transform.position.X(),
		(int)m_Transform.position.Y(),
		(int)m_Size.X(),
		(int)m_Size.Y(),
	};

	m_Button->Update();

	if (m_Active && !SDL_IsTextInputActive())
	{
		SDL_StartTextInput();
	}

	if (m_Active)
	{
		if (Input::Event().type == SDL_TEXTINPUT)
		{
			m_TextString += Input::Event().text.text;
			m_Text->SetLabel(m_TextString);
		}
		if (Input::Event().type == SDL_KEYDOWN && Input::Event().key.keysym.sym == SDLK_BACKSPACE)
		{
			if (!m_TextString.empty())
			{
				m_TextString.pop_back();
				m_Text->SetLabel(m_TextString);
			}
		}
	}
}

void UIInputBox::Clear()
{
	m_Text->SetLabel("|");
}