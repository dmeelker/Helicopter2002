#include "Cave.h"
#include "Game.h"
#include "Lerp.h"
#include "Player.h"
#include "Vector.h"
#include <raylib.h>
#include <stdio.h>

#define MAX_SPEED 8

const Size playerSize = { 70, 50 };
const Vector gravity = { 0, 20.0f };
const Vector liftSpeed = { 0, -42.0f };

Player player = { .position = { 600, 300 }, .speed = { 0, 0 } };

Camera2D camera;

bool started = false;
bool crashed = false;
float crashTime = 0.0f;
int score = 0;
int xOffset = 0;

static void clampVelocity(Vector* speed)
{
	if (speed->y > MAX_SPEED)
	{
		speed->y = MAX_SPEED;
	}
	else if (speed->y < -MAX_SPEED)
	{
		speed->y = -MAX_SPEED;
	}
}

static void updateCameraLocation()
{
	camera.target.x = player.position.x + 200;
	xOffset = player.position.x - 200;
}

static void resetGame()
{
	started = false;
	crashed = false;
	levelReset();

	player = (Player){ { 300, (SCREEN_HEIGHT / 2) - (playerSize.height / 2)}, {0, 0} };
	updateCameraLocation();
}

static int getScore()
{
	return (player.position.x - 10) / 10;
}

void gameInitialize()
{
	camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.target = (Vector2){ 0.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;
	camera.rotation = 0.0f;

	resetGame();
}

void gameUpdate(float frameTime)
{
	if (!started)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			started = true;
		}
		return;
	}

	player.position = vectorAdd(player.position, player.speed);
	player.position.x += frameTime * 300.0; // 100.0

	Rect playerRect = { player.position.x, player.position.y, playerSize.width, playerSize.height };

	if (levelCollides(playerRect))
	{
		crashed = true;
		crashTime = GetTime();
	}

	updateCameraLocation();

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

	clampVelocity(&player.speed);

	levelUpdate(xOffset);
}

void gameRender()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	BeginMode2D(camera);
	levelRender();

	DrawRectangle(player.position.x, player.position.y, playerSize.width, playerSize.height, RED);
	EndMode2D();

	char buffer[100];
	sprintf(buffer, "Score: %d", score);

	DrawText(buffer, 5, 5, 20, WHITE);

	EndDrawing();
}
