#include "sprite.h"




SpriteInfo DefaultSprite{ 0 };

const SpriteInfo& GetSprite(int id) {
	if (id < 0 || id > int(Sprites.size()))
		return DefaultSprite;

	return Sprites[id];
}

void DrawSprite(SpriteInfo& sprite, float x, float y, float rotation, float scale, Color tint)
{
	
	Texture2D texture = GetTexture(sprite.textureID);

	DrawTexturePro(
		texture,
		Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
		Rectangle{ x, y, sprite.width * scale,sprite.height * scale },
		Vector2{ scale * sprite.width / 2, scale * sprite.height / 2 },
		rotation,
		tint);
}




void DrawEffect(SpriteInfo& sprite, EffectInstance& effect) {
	effect.Lifetime -= GetFrameTime();
	
	if (effect.Lifetime < 0) {
		return;
	}
	
	float param = effect.Lifetime / effect.MaxLifetime;
	float rotation = 0;
	float alpha = 1;
	float scale = 1;

	Vector2 pos = effect.Position;

	switch (effect.Effect)
	{
	case EffectType::Fade:
		alpha = param;
		break;

	case EffectType::RiseFade:
		alpha = param;
		pos.y -= (1.0f - param) * 30;
		break;

	case EffectType::RotateFade:
		rotation = (1.0f - param) * 360;
		
		alpha = param;
		
		break;

	case EffectType::ScaleFade:
		alpha = param;
		scale = 1 + (1.0f - param);
		break;
	}

	DrawSprite(sprite, pos.x, pos.y, rotation, scale, ColorAlpha(WHITE, alpha));
	
	
}

Mob::Mob(SpriteID spriteID, float x, float y) : spriteID(spriteID), x(x), y(y) {
	sprite = GetSprite(spriteID);
}

void Mob::Draw() {
	
	DrawSprite(sprite, x, y, rotation, scale, tint);
	
}

void Mob::DrawCollisionBox() {
	DrawRectangleLinesEx(CollisionRec(), 1, YELLOW);
}

Rectangle Mob::CollisionRec() {

	
	return Rectangle{ x + sprite.CollisionRec.x - sprite.CollisionRec.width / 2,
		y + sprite.CollisionRec.y - sprite.CollisionRec.height / 2,
		sprite.CollisionRec.width,
		sprite.CollisionRec.height };

}

void Mob::SetEffect(float MaxLifetime, EffectType Effect) {
	effect = {
		{ x, y },
		Effect,
		MaxLifetime,
		MaxLifetime
	};
}

void Mob::ShowEffect() {
	DrawEffect(sprite, effect);
}

void Button::Draw() {

	int textWidth = MeasureText(text, fontSize);

	if (isClicked) {
		DrawRectangle(x, y, width, height, pressed_color);
	}
	else {
		DrawRectangle(x, y, width, height, color);
	}
	DrawText(text, x, y + height / 2 - fontSize / 2, fontSize, fontColor);
	
}



bool Button::CheckClicked() {
	
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), Rectangle{ x, y, width, height })) {
		
		isClicked = true;
		return true;
	}
	return false;
	
}

void StatusText::Draw() {
	
	textWidth = MeasureText(TextFormat("%s : %d", status, value), size);
	DrawText(TextFormat("%s : %d", status, value), x, y, size, color);
	
	
}