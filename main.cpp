
#include <iostream>

#include "common.h"
#include "game.h"
#include "loading.h"

#define WINDOW_WIDTH 960
#define WINDOW_HIGHT 540



int main(int argc, char** argv) {

	ApplicationState = ApplicationStates::Menu;

	InitWindow(WINDOW_WIDTH, WINDOW_HIGHT, "Plane Fight");
	InitAudioDevice();
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	RoadResources();
	StartGame();
	
	SetMasterVolume(0.1f);

	while (!WindowShouldClose() && ApplicationState != ApplicationStates::Quiting) {
		
		switch (ApplicationState)
		{
		case ApplicationStates::Loading:
			UpdateLoad();
			break;
		case ApplicationStates::Menu:
			UpdateMainMenu();
			break;
		case ApplicationStates::Running:
			UpdateGame();
			UpdateScreen();
			break;
		case ApplicationStates::Paused:
			UpdatePaused();
			break;
		case ApplicationStates::GameOver:
			UpdateGameOver();
			break;
		}
		
		
		BeginDrawing();
			ClearBackground(SKYBLUE);

			DrawSprites();
			DrawScreen();

			DrawFPS(20, GetScreenHeight() - 20);

		EndDrawing();
	}

	EndGame();
	
	return 0;
}