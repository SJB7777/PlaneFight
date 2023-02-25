#include "game.h"

std::random_device rd; // 시드값 얻기
std::default_random_engine eng(rd()); // 난수 생성 엔진 초기화
std::uniform_real_distribution<> distr(0, 1); // 균등분포 정의

Mob player(PlayerSprite);

Button* pause_btn = new Button();
Button* quit_btn = new Button();


StatusText* kill_status = new StatusText();
StatusText* time_status = new StatusText();

std::vector<Mob> bullets;
std::vector<Mob> enemies;

int kill_count;
Button* buttons[2] = { pause_btn, quit_btn };
StatusText* statuses[2] = { kill_status, time_status };

#define BULLET_TIME_MAX 6
int bullet_time = BULLET_TIME_MAX;

double GameClock;

float GetGameTime() { return float(GameClock); }

void StartGame() {
	GameClock = 0;
	kill_count = 0;
	// GUI
	// pause button
	pause_btn->width = 30;
	pause_btn->height = 30;
	pause_btn->x = GetScreenWidth() - pause_btn->width - 100;
	pause_btn->y = pause_btn->height + 50;
	
	pause_btn->text = "Pause";
	// buttons.push_back(std::move(pause_btn));

	// quit button
	quit_btn->width = 30;
	quit_btn->height = 30;
	quit_btn->x = pause_btn->x + pause_btn->width + 30;
	quit_btn->y = pause_btn->y;
	quit_btn->text = "Quit";
	
	// buttons.push_back(std::move(quit_btn));

	// kill status text
	// statuses.push_back(std::move(kill_status));
	kill_status->x = 10;
	kill_status->y = 10;
	kill_status->size = 20;
	kill_status->status = "kill";
	

	// time status text
	// statuses.push_back(std::move(time_status));
	time_status->x = kill_status->x;
	time_status->y = kill_status->y + kill_status->size;
	time_status->size = 20;
	time_status->status = "time";
	

	// player
	player.x = GetScreenWidth() / 2.0f;
	player.y = GetScreenHeight() - 50.0f;
	player.speed = 300;
	
	
	
}

void UpdateGame() {

	
	
	if (IsKeyDown(KEY_LEFT)) {
		player.x -= player.speed * GetFrameTime();
		if (player.x <= 0) {
			player.x = 0;
		}
	}
	if (IsKeyDown(KEY_RIGHT)) {
		player.x += player.speed * GetFrameTime();
		if (player.x >= GetScreenWidth()) {
			player.x = (float) GetScreenWidth();
		}
	}

	if (bullet_time >= BULLET_TIME_MAX) {
		bullet_time = BULLET_TIME_MAX;
	}
	else {
		bullet_time++;
	}
		
	
	if (IsKeyDown(KEY_SPACE) && bullet_time == BULLET_TIME_MAX) {
		PlaySoundMulti(GetSound(GunFireSound));
		bullet_time = 0;
		
		Mob bullet(BulletSprite, player.x, player.y);
		
		bullet.speed = 500;
		
		
		bullets.push_back(bullet);
	}
	

	
	for (auto& bullet : bullets) {
		bullet.y -= bullet.speed * GetFrameTime();

		if (bullet.y <= -bullet.sprite.height / 2) {

			bullet.speed = 0;
			bullet.isOnScreen = false;
		}
	}
	


	if (distr(eng) >= 0.98f) {
		Mob enemy(EnemySprite);

		enemy.x = GetScreenWidth() * distr(eng);
		enemy.y = -enemy.height;
		
		enemy.speed = 100;
		
		enemies.push_back(enemy);
	}

	if (distr(eng) >= 0.99f) {
		Mob bomber(Enemy2Sprite);

		bomber.x = GetScreenWidth() * distr(eng);
		bomber.y = -bomber.height;

		bomber.speed = 100;

		enemies.push_back(bomber);
	}

	for (auto& enemy : enemies) {
		enemy.y += enemy.speed * GetFrameTime();

		if (enemy.y >= GetScreenHeight() + enemy.height / 2) {

			enemy.speed = 0;
			enemy.isOnScreen = false;
		}
	}

	
	// collision check
	for (auto& enemy : enemies) {
		for (auto& bullet : bullets) {
			if (enemy.isOnScreen && bullet.isOnScreen) {
				if (CheckCollisionRecs(enemy.CollisionRec(), bullet.CollisionRec())) {
					enemy.SetEffect(1, EffectType::RiseFade);
					enemy.isOnScreen = false;
					enemy.speed = 0;
					// enemy.y = -enemy.height;
					bullet.isOnScreen = false;
					bullet.speed = 0;
					// bullet.y = -bullet.height;
					kill_count += 1;
				}
			}
		}
	}

	for (auto& enemy : enemies) {
		if (enemy.isOnScreen && player.isOnScreen) {
			if (CheckCollisionRecs(enemy.CollisionRec(), player.CollisionRec())) {
				std::cout << "Game Over" << std::endl;
				ApplicationState = ApplicationStates::GameOver;
			}
		}
	}

	
}

void UpdateScreen() {
	pause_btn->CheckClicked();

	kill_status->value = kill_count;
	time_status->value = GetGameTime();

	GameClock += GetFrameTime();

	if (pause_btn->CheckClicked()) {
		ApplicationState = ApplicationStates::Paused;
	}
	if (quit_btn->CheckClicked()) {
		ApplicationState = ApplicationStates::Quiting;
	}
}

void UpdateLoad() {}

void UpdateMainMenu() {

	

	Screen::DimScreen();
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), LIME);
	// message
	const char* text1 = "Game Menu";
	const char* text2 = "Press any button to Start";
	int text1Width = MeasureText(text1, 60);
	int text2Width = MeasureText(text2, 30);
	DrawText(text1, GetScreenWidth() / 2 - text1Width / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
	DrawText(text2, GetScreenWidth() / 2 - text2Width / 2, GetScreenHeight() / 2 + 30, 30, BLACK);
	if (IsAnyKeyPressed()) {
		ApplicationState = ApplicationStates::Running;
		text1 = nullptr;
		text2 = nullptr;
	}
	

}

void UpdatePaused() {
	

	Screen::DimScreen();
	// message
	const char* text1 = "Game Paused";
	const char* text2 = "Press any button to Start";
	int text1Width = MeasureText(text1, 60);
	int text2Width = MeasureText(text2, 30);
	DrawText(text1, GetScreenWidth() / 2 - text1Width / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
	DrawText(text2, GetScreenWidth() / 2 - text2Width / 2, GetScreenHeight() / 2 + 30, 30, BLACK);
	if (IsAnyKeyPressed()) {
		ApplicationState = ApplicationStates::Running;
		pause_btn->isClicked = false;
		text1 = nullptr;
		text2 = nullptr;
	}
	
}

void UpdateGameOver() {

	

	Screen::DimScreen();
	// message
	const char* text1 = "Game Over";
	const char* text2 = "Press any button to Restart";
	int text1Width = MeasureText(text1, 60);
	int text2Width = MeasureText(text2, 30);
	DrawText(text1, GetScreenWidth() / 2 - text1Width / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
	DrawText(text2, GetScreenWidth() / 2 - text2Width / 2, GetScreenHeight() / 2 + 30, 30, BLACK);
	if (IsAnyKeyPressed()) {
	
		// std::vector<Sprite*>().swap(bullets);
		// std::vector<Sprite*>().swap(enemies);
		
		bullets.clear();
		enemies.clear();

		StartGame();
		
		text1 = nullptr;
		text2 = nullptr;

		ApplicationState = ApplicationStates::Menu;
	
	}
	
}

void EndGame() {
	std::cout << "EndGame" << std::endl;

	
	for (auto& status : statuses) {
		delete status;
	}
	
	/// statuses.clear();
	
	for (auto& button : buttons) {
		delete button;
	}
	//buttons.clear();
	
	DeleteResources();
}



void DrawSprites() {
	// draw functions
	player.Draw();
	player.DrawCollisionBox();
	for (auto& bullet : bullets) {
		if (bullet.isOnScreen) {
			bullet.Draw();
			bullet.DrawCollisionBox();
		}
	}
	for (auto& enemy : enemies) {
		if (enemy.isOnScreen) {
			enemy.Draw();
			enemy.DrawCollisionBox();
		}
		
		enemy.ShowEffect();
	}
	
}

void DrawScreen() {

	for (auto& status : statuses) {
		status->Draw();
	}

	for (auto& button : buttons) {
		button->Draw();
	}
}