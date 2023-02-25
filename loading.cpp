#include "loading.h"


std::vector<Texture2D> LoadedTextures;

std::vector<Sound> LoadedSounds;

Texture2D DefaultTexture = { 0 };
Sound DefaultSound = { 0 };

void RoadResources() {

	for (int i = 0; i < TextureToLoad.size(); i++) {
		LoadedTextures.push_back(LoadTexture(TextureToLoad[i]));
	}
	for (int i = 0; i < SoundToLoad.size(); i++) {
		LoadedSounds.push_back(LoadSound(SoundToLoad[i]));
	}
}

const Texture& GetTexture(int id) {
	if (id < 0 || id > int(LoadedTextures.size()))
		return DefaultTexture;

	return LoadedTextures[id];
}

const Sound& GetSound(int id) {
	if (id < 0 || id > int(LoadedSounds.size()))
		return DefaultSound;

	return LoadedSounds[id];
}

void DeleteResources() {
	for (const auto& texture : LoadedTextures) {
		UnloadTexture(texture);
	}
	for (const auto& sound : LoadedSounds) {
		UnloadSound(sound);
	}
}


