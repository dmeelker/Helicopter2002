#include "assets/Audio.h"
#include "assets/Fonts.h"
#include "Cave.h"
#include "Constants.h"
#include "Game.h"
#include "Lerp.h"
#include "Particles.h"
#include "Player.h"
#include "Screens.h"
#include "Settings.h"
#include "Text.h"
#include "Textures.h"
#include "utils/Timer.h"
#include "Vector.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>

#define MAX_SPEED 500

const Size playerSize = { 70, 35 };
const Vector gravity = { 0, 1200.0f };
const Vector liftSpeed = { 0, -2560.0f };

Player player = { .position = { 600, 300 }, .speed = { 0, 0 } };
bool accelerating = false;
double accelerateStartTime = 0;
double accelerateEndTime = 0;

Camera2D camera;

bool started = false;
bool crashed = false;
double crashTime = 0.0f;
int score = 0;
int highscore = 0;
int xOffset = 0;

Timer smokeTimer;

double highscoreTime = 0;
bool gotHighscore = false;

// Foward declarations
int loadHighscore();
void saveHighscore(int score);

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
	xOffset = (int)player.position.x - 200;
}

static void resetGame()
{
	started = false;
	accelerating = false;
	crashed = false;
	score = 0;
	smokeTimer = timerCreate(0.1f);
	gotHighscore = false;

	levelReset();
	particlesReset();

	player = (Player){ { 300, (float)CENTER(SCREEN_HEIGHT, playerSize.height)}, {0, 0} };
	updateCameraLocation();
}

static int getScore()
{
	return (int)((player.position.x - 10.0f) / 10.0f);
}

void gameInitialize()
{
	camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.target = (Vector2){ 0.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;
	camera.rotation = 0.0f;

	highscore = loadHighscore();
	resetGame();
}

static void updateSmoke(Particle* particle, float age)
{
	particle->zoom = lerp(age, 1.0f, 3.0f);
	particle->alpha = lerp(age, 1.0f, 0.0f);
}

void gameUpdate(float frameTime)
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		screenSwitch(SCREEN_MENU);
		return;
	}

	if (!started)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			started = true;
		}
		return;
	}

	particlesUpdate(frameTime);

	if (crashed)
	{
		if (timerUpdate(&smokeTimer))
		{
			particleCreate(vectorAdd(player.position, (Vector) { playerSize.width / 2.0f, playerSize.height / 2.0f }), (Vector) { (float)random(-5, 5), -30 }, (Vector) { 0, 0 }, 5000, & updateSmoke);
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			resetGame();
			started = true;
		}
		return;
	}

	player.position = vectorAdd(player.position, vectorMultiply(player.speed, frameTime));
	player.position.x += frameTime * 300.0f;

	Rect playerRect = { player.position.x, player.position.y, (float)playerSize.width, (float)playerSize.height };

	if (levelCollides(playerRect))
	{
		if (score > highscore)
		{
			highscore = score;
			saveHighscore(highscore);
		}

		crashed = true;
		crashTime = GetTime();

		if (settings.enableSound)
		{
			StopSound(audio.heli);
			PlaySound(audio.crash);
		}
	}

	updateCameraLocation();

	player.speed = vectorAdd(player.speed, vectorMultiply(gravity, frameTime));

	if (IsMouseButtonDown(0))
	{
		if (!accelerating)
		{
			accelerateStartTime = GetTime();

			if (settings.enableSound)
			{
				PlaySound(audio.heli);
			}
		}

		float blendProgress = (float)mind((GetTime() - accelerateStartTime) / 0.2f, 1.0f);
		SetSoundVolume(audio.heli, blendProgress);

		player.speed = vectorAdd(player.speed, vectorMultiply(liftSpeed, frameTime));
		accelerating = true;
	}
	else
	{
		if (accelerating)
		{
			accelerateEndTime = GetTime();
		}

		float blendProgress = (float)mind((GetTime() - accelerateEndTime) / 0.2f, 1.0f);
		SetSoundVolume(audio.heli, 1.0f - blendProgress);
		accelerating = false;
	}

	if (timerUpdate(&smokeTimer))
	{
		particleCreate(vectorAdd(player.position, (Vector) { 0, 10 }), (Vector) { 0, -5 }, (Vector) { 0, 0 }, 1000, & updateSmoke);
	}

	clampVelocity(&player.speed);
	levelUpdate(xOffset);


	score = getScore();

	if (highscore > 0 && score > highscore && !gotHighscore)
	{
		gotHighscore = true;
		highscoreTime = GetTime();
	}
}

static void renderHelicopter()
{
	int offset = crashed ? 0 : ((int)(GetTime() * 1000.0f) / 50) % 3;
	Rectangle source = { (float)offset * playerSize.width, 0, (float)playerSize.width, (float)playerSize.height };
	Rectangle target = { (float)(int)player.position.x , (float)(int)player.position.y , (float)playerSize.width, (float)playerSize.height };

	float rotation = accelerating ? 5.f : 0.f;

	//DrawRectangle((int)target.x, (int)target.y, target.width, target.height, RED);

	target.x += (playerSize.width / 2);
	target.y += (playerSize.height / 2);

	DrawTexturePro(textures.helicopter, source, target, (Vector2)
	{
		(playerSize.width / 2.0f), (playerSize.height / 2.0f)
	}, rotation, WHITE);
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

	if (!started)
	{
		renderTextCenteredWiggle(&TEXT_YELLOW_LARGE, "CLICK TO FLY", (Vector2) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	}
	else if (crashed)
	{
		float timeSinceCrash = (float)GetTime() - (float)crashTime;
		float progress = easeOutCubic(minf(timeSinceCrash / 0.5f, 1.0f));

		Vector2 location = {
			lerp(progress, -300, SCREEN_WIDTH / 2),
			SCREEN_HEIGHT / 2 };

		renderTextCenteredWiggle(&TEXT_YELLOW_LARGE, "CRASHED", location);

		if (gotHighscore)
		{
			location = (Vector2){
			lerp(progress, -300, SCREEN_WIDTH / 2),
			(SCREEN_HEIGHT / 2) + 50 };

			renderTextCenteredWiggle(&TEXT_YELLOW_MEDIUM, "NEW HIGH SCORE", location);
		}
	}

	if (!crashed && gotHighscore)
	{
		float timeSinceHighscore = (float)GetTime() - (float)highscoreTime;

		if (timeSinceHighscore < 1.0f)
		{
			float progress = easeOutCubic(timeSinceHighscore / 1.0f);
			Vector2 location = {
				lerp(progress, -300, SCREEN_WIDTH / 2),
				SCREEN_HEIGHT / 2 };

			renderTextCenteredWiggle(&TEXT_YELLOW_LARGE, "HIGH SCORE", location);
		}
		else if (timeSinceHighscore < 2.0f)
		{
			float progress = easeOutCubic((timeSinceHighscore - 1.0f) / 1.0f);
			Vector2 location = {
				lerp(progress, SCREEN_WIDTH / 2, SCREEN_WIDTH + 300),
				SCREEN_HEIGHT / 2 };

			renderTextCenteredWiggle(&TEXT_YELLOW_LARGE, "HIGH SCORE", location);
		}
	}

	char buffer[100];

	if (highscore > 0)
	{
		sprintf_s(buffer, 100, "%d", highscore);
		renderTextCentered(&TEXT_ORANGE_SMALL, buffer, (Vector2) { SCREEN_WIDTH / 2, 60 });
	}

	sprintf_s(buffer, 100, "%d", score);
	renderTextCentered(&TEXT_ORANGE_MEDIUM, buffer, (Vector2) { SCREEN_WIDTH / 2, 25 });
	DrawFPS(10, 10);
	EndDrawing();
}

int loadHighscore()
{
	FILE* file = fopen("data.dat", "rb");
	if (file == NULL)
	{
		// If the file doesn't exist or can't be opened, return 0 as the default high score
		return 0;
	}

	unsigned char buffer[4];
	size_t read = fread(buffer, sizeof(buffer), 1, file);

	if (read == 0)
	{
		fclose(file);
		return 0;
	}

	int* highscore = (int*)buffer;
	fclose(file);

	return *highscore;
}


void saveHighscore(int score)
{
	FILE* file = fopen("data.dat", "wb");
	if (file == NULL)
	{
		printf("Failed to save highscore\n");
		return;
	}

	unsigned char* buffer = (unsigned char*)&score;
	fwrite(buffer, sizeof(int), 1, file);
	fclose(file);
}