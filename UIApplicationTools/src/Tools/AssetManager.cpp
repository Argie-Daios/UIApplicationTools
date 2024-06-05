#include "AssetManager.h"

#include "Core/Macros.h"
#include "Rendering/Renderer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

UIHashMap<UIString, UITexture*> AssetManager::s_Textures;
UIHashMap<UIString, UIFont*> AssetManager::s_Fonts;

void AssetManager::Init()
{
	// Currently does nothing
}

void AssetManager::Shutdown()
{
	// Delete Textures
	for (auto& it : s_Textures)
	{
		SDL_DestroyTexture(it.second->Texture);
		delete it.second;
	}

	// Delete Fonts
	for (auto& it : s_Fonts)
	{
		TTF_CloseFont(it.second->Font);
		delete it.second;
	}
}

UITexture* AssetManager::LoadTexture(const UIString& name, const UIString& filepath)
{
	UIASSERT(!IsInvalid(name), "ERROR: INVALID ASSET NAME");
	UIASSERT(!IsDuplicate(name, UIAssetType::UITexture), "There is already a texture with the name: " +
		name + "!!");

	SDL_Surface* surface = IMG_Load(filepath.c_str());
	UIASSERT(surface, "Texture surface failed to load!! [filepath: " + filepath + "]");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::s_Renderer, surface);
	UIASSERT(texture, "Texture failed to construct!! [filepath: " + filepath + "]");

	UITexture* uiTexture = new UITexture;
	UIASSERT(uiTexture, "Malloc failure!!");
	uiTexture->Texture = texture;
	SDL_QueryTexture(texture, 0, 0, &uiTexture->Width, &uiTexture->Height);
	s_Textures.emplace(name, uiTexture);
	SDL_FreeSurface(surface);

	return s_Textures.at(name);
}

UITexture* AssetManager::ReceiveTexture(const UIString& name)
{
	UIASSERT(!IsInvalid(name), "ERROR: INVALID ASSET NAME");
	UIASSERT(IsDuplicate(name, UIAssetType::UITexture), "There is no such texture with the name: " +
		name + "!!");

	return s_Textures.at(name);
}

void AssetManager::DeleteTexture(const UIString& name)
{
	UIASSERT(!IsInvalid(name), "ERROR: INVALID ASSET NAME");
	UIASSERT(IsDuplicate(name, UIAssetType::UITexture), "There is no such texture with the name: " +
		name + "!!");

	auto& it = s_Textures.find(name);
	SDL_DestroyTexture(it->second->Texture);
	delete it->second;
	s_Textures.erase(it);
}

UIFont* AssetManager::LoadFont(const UIString& name, const UIString& filepath, UIUnsignedInt fontSize)
{
	UIASSERT(!IsInvalid(name), "ERROR: INVALID ASSET NAME");
	UIASSERT(!IsDuplicate(name, UIAssetType::UIFont), "There is already a font with the name: " +
		name + "!!");

	TTF_Font* font = TTF_OpenFont(filepath.c_str(), fontSize);
	UIASSERT(font, "Font failed to load!! [filename: " + filepath + "]");

	UIFont* uiFont = new UIFont;
	UIASSERT(uiFont, "Malloc Failure!!");
	uiFont->Font = font;
	uiFont->FontSize = fontSize;
	s_Fonts.emplace(name, uiFont);

	return s_Fonts.at(name);
}

UIFont* AssetManager::ReceiveFont(const UIString& name)
{
	UIASSERT(!IsInvalid(name), "ERROR: INVALID ASSET NAME");
	UIASSERT(IsDuplicate(name, UIAssetType::UIFont), "There is no such font with the name: " +
		name + "!!");

	return s_Fonts.at(name);
}

bool AssetManager::IsInvalid(const UIString& name)
{
	return name == invalidName;
}

bool AssetManager::IsDuplicate(const UIString& name, const UIAssetType& type)
{
	switch (type)
	{
	case UIAssetType::UITexture: return s_Textures.find(name) != s_Textures.end();
	case UIAssetType::UIFont: return s_Fonts.find(name) != s_Fonts.end();
	}

	UIASSERT(false, "Invalid UIAssetType!!");
	return false;
}