#ifndef __SPRITE_H__
#define __SPRITE_H__


#include "common.h"
#include "loading.h"

struct SpriteInfo{
	int textureID = -1;
	float width = 0;
	float height = 0;
	Rectangle CollisionRec = {
		0, 0, 0, 0
	};
};

inline std::vector<SpriteInfo> Sprites = {
	SpriteInfo {
		PlayerTexture,
		90, 90,
		{0, -10, 90, 30},
	},
	SpriteInfo {
		BulletTexture,
		10, 30,
		{0, 0, 10, 30}
	},
	SpriteInfo {
		EnemyTexture,
		50, 50,
		{0, -10, 50, 30}
	},
	SpriteInfo {
		Enemy2Texture,
		50, 50,
		{0, 5, 50, 20}
	}

};

enum SpriteID {
	PlayerSprite,
	BulletSprite,
	EnemySprite,
	Enemy2Sprite,
};

enum class EffectType
{
	Fade,
	RiseFade,
	RotateFade,
	ScaleFade
};

struct EffectInstance
{
	Vector2 Position = { 0,0 };
	EffectType Effect = EffectType::Fade;
	float Lifetime = 1;
	float MaxLifetime = 1;
};

const SpriteInfo& GetSprite(int id);

void DrawSprite(SpriteInfo& sprite, float x, float y, float rotation, float scale, Color tint);

class Mob {
public:
	Mob(SpriteID spriteID, float x = 0, float y = 0);
	int spriteID = -1;
	
	float x = 0, y = 0;
	float speed = 0;
	float rotation = 0;
	float scale = 1;
	Color tint = WHITE;

	bool isOnScreen = true;

	void Draw();
	void DrawCollisionBox();
	Rectangle CollisionRec();
	SpriteInfo sprite = { 0 };

	__declspec(property(get = GetWidth)) float width;
	__declspec(property(get = GetHeight)) float height;

	float GetWidth() const { return sprite.width * scale; }
	float GetHeight() const { return sprite.height * scale; }

	EffectInstance effect = {
					{ x, y },
					EffectType::Fade,
					0,
					1
					};

	void SetEffect(float MaxLifetime, EffectType Effect);
	void ShowEffect();
private:
	
};



void DrawEffect(SpriteInfo& sprite, EffectInstance& effect);

class Button {
public:
	
	float x, y;
	float width, height;
	Color color{ 127, 106, 79, 125 };
	Color pressed_color{128, 149, 176, 125};
	Color fontColor{ 0, 0, 0, 255};

	void Draw();
	bool CheckClicked();

	const char* text = nullptr;
	int fontSize = 10;
	bool isClicked = false;
	
private:
	
};

class StatusText {
public:
	float x, y;
	float size;
	Color color{ 80, 80, 80, 125 };
	const char* status = nullptr;
	int value = 0;
	int textWidth;
	void Draw();
};
#endif // __SPRITE_H__