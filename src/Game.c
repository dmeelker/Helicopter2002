#include "Cave.h"
#include "Constants.h"
#include "Game.h"
#include "Lerp.h"
#include "Particles.h"
#include "Player.h"
#include "Textures.h"
#include "Vector.h"
#include <raylib.h>
#include <stdio.h>

#define MAX_SPEED 8

const Size playerSize = { 70, 35 };
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
	score = 0;
	levelReset();
	particlesReset();

	player = (Player){ { 300, CENTER(SCREEN_HEIGHT, playerSize.height)}, {0, 0} };
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

static void updateSmoke(Particle* particle, float age)
{
	particle->zoom = lerp(age, 0.5f, 2.0f);
	particle->alpha = lerp(age, 1.0f, 0.0f);
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

	if (crashed)
	{
		if (GetTime() - crashTime > 2)
		{
			resetGame();
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

	if (IsMouseButtonDown(0))
	{
		player.speed = vectorAdd(player.speed, vectorMultiply(liftSpeed, frameTime));
	}

	particleCreate(player.position, (Vector) { 0, -5 }, (Vector) { 0, 0 }, 1000, & updateSmoke);

	clampVelocity(&player.speed);
	levelUpdate(xOffset);
	particlesUpdate(frameTime);

	score = getScore();
}

static void renderHelicopter()
{
	int offset = ((int)(GetTime() * 1000.0f) / 50) % 3;
	Rectangle source = { offset * playerSize.width, 0, playerSize.width, playerSize.height };
	Rectangle target = { (int)player.position.x, (int)player.position.y, playerSize.width, playerSize.height };
	DrawTexturePro(textures.helicopter, source, target, (Vector2) { 0, 0 }, 0.0f, WHITE);
}

void gameRender()
{
	BeginDrawing();

	ClearBackground((Color) { 48, 81, 130, 255 });

	BeginMode2D(camera);
	levelRender();

	renderHelicopter();
	particlesRender();


	EndMode2D();

	char buffer[100];
	sprintf(buffer, "Score: %d", score);

	DrawText(buffer, 5, 5, 20, WHITE);

	EndDrawing();
}
