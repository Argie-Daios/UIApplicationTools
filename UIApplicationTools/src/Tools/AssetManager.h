#pragma once

#include "Core/UIDefinitions.h"

inline const UIString invalidName = "--INVALID--";

enum class UIAssetType : UIUnsignedByte
{
	UITexture,
	UIFont
};

struct UITexture
{
	struct SDL_Texture* Texture;
};

typedef struct _TTF_Font TTF_Font;
struct UIFont
{
	TTF_Font* Font;
	UIUnsignedInt FontSize;
};

class AssetManager
{
public:
	static void Init();
	static void Shutdown();

	static UITexture* LoadTexture(const UIString& name, const UIString& filepath);
	static UITexture* ReceiveTexture(const UIString& name);
	static void DeleteTexture(const UIString& name);

	static UIFont* LoadFont(const UIString& name, const UIString& filepath, UIUnsignedInt fontSize);
	static UIFont* ReceiveFont(const UIString& name);
public:
	static bool IsInvalid(const UIString& name);
private:
	static bool IsDuplicate(const UIString& name, const UIAssetType& type);
private:
	static UIHashMap<UIString, UITexture*> s_Textures;
	static UIHashMap<UIString, UIFont*> s_Fonts;
};