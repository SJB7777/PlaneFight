#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "sprite.h"
#include "screen.h"
#include "loading.h"

void StartGame();

void EndGame();


void UpdateLoad();
void UpdateMainMenu();
void UpdateGame();
void UpdateScreen();
void UpdatePaused();
void UpdateGameOver();

void DrawSprites();
void DrawScreen();

#endif // __GAME_H__

