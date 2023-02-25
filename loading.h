#ifndef __LOADING_H__
#define __LOADING_H__

#include "common.h"

void RoadResources();
const Texture& GetTexture(int id);
const Sound& GetSound(int id);
void DeleteResources();

enum TextureID {
	PlayerTexture,
	BulletTexture,
	EnemyTexture,
	Enemy2Texture
};

enum SoundID {
	GunFireSound
};

inline std::vector<const char*> TextureToLoad = {
	"asset/player.png",
	"asset/bullet.png",
	"asset/enemy.png",
	"asset/enemy2.png"
};

inline std::vector<const char*> SoundToLoad = {
	"asset/gun_fire.wav"
};
#endif // __LOADING_H__
