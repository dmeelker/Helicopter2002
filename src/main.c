#include "Cave.h"
#include "Constants.h"
#include "Player.h"
#include "raylib.h"
#include "Rect.h"
#include "Vector.h"
#include <stdbool.h>
#include <stdio.h>

#define PLAYER_SIZE 20

const Vector gravity = { 0, 10.0f };
const Vector liftSpeed = { 0, -22.0f };

Player player = { { 400, 300 }, { 0, 0 } };

Camera2D camera;

bool crashed = false;
float crashTime = 0.0f;
int score = 0;

void resetGame();

void update(float frameTime)
{
	player.position = vectorAdd(player.position, player.speed);
	player.position.x += frameTime * 100.0;

	Rect playerRect = { player.position.x, player.position.y, PLAYER_SIZE, PLAYER_SIZE };

	if (levelCollides(playerRect))
	{
		crashed = true;
		crashTime = GetTime();
	}

	camera.target.x = player.position.x + 200; // = (Vector2){ player.position.x, player.position.y };

	player.speed = vectorAdd(player.speed, vectorMultiply(gravity, frameTime));

	if (crashed)
	{
		if (GetTime() - crashTime > 2)
		{
			resetGame();
		}
	}
	else
	{
		score = getScore();
		if (IsMouseButtonDown(0))
		{
			player.speed = vectorAdd(player.speed, vectorMultiply(liftSpeed, frameTime));
		}
	}
}

void render()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	BeginMode2D(camera);
	levelRender();

	DrawRectangle(player.position.x, player.position.y, PLAYER_SIZE, PLAYER_SIZE, RED);
	EndMode2D();

	char buffer[100];
	sprintf(buffer, "Score: %d", score);

	DrawText(buffer, 5, 5, 20, WHITE);

	EndDrawing();
}

int getScore()
{
	return player.position.x - 10;
}

void resetGame()
{
	crashed = false;
	levelClear();
	levelGeneratePath();

	player = (Player){ { 10, (SCREEN_HEIGHT / 2) - (PLAYER_SIZE / 2)}, {0, 0} };
	camera.target = (Vector2){ 0.0f, SCREEN_HEIGHT / 2.0f };
}

int main(void)
{
	camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.target = (Vector2){ 0.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;
	camera.rotation = 0.0f;

	resetGame();

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Elicopter");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		update(GetFrameTime());
		render();
	}
	CloseWindow();

	return 0;
}
