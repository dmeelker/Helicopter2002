#include "Particles.h"
#include "Textures.h"
#include <raylib.h>

#define MAX_PARTICLES 100

Particle particles[MAX_PARTICLES];

static Particle* allocateParticle()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (!particles[i].used)
		{
			particles[i].used = true;
			return &particles[i];
		}
	}
	return NULL;
}

void particlesReset()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		particles[i].used = false;
	}
}

void particlesUpdate(float frameTime)
{
	int time = (int)(GetTime() * 1000.0);

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (!particles[i].used)
		{
			continue;
		}

		Particle* particle = &particles[i];
		float age = (time - particle->creationTime) / (float)particle->maxAge;

		particle->position = vectorAdd(particle->position, vectorMultiply(particle->speed, frameTime));

		if (particle->updateFunc != NULL)
		{
			particle->updateFunc(particle, age);
		}

		if (age >= 1.0f)
		{
			particle->used = false;
		}
	}
}

void particlesRender()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (particles[i].used)
		{
			DrawTextureEx(textures.smoke, (Vector2) { particles[i].position.x, particles[i].position.y }, 0.0f, particles[i].zoom, (Color) { 255, 255, 255, (unsigned char)(particles[i].alpha * 255.0f) });
		}
	}
}

void particleCreate(Vector position, Vector speed, Vector acceleration, int maxAge, ParticleFunc updateFunc)
{
	Particle* particle = allocateParticle();

	if (particle == NULL)
	{
		return;
	}

	particle->position = position;
	particle->speed = speed;
	particle->acceleration = acceleration;
	particle->creationTime = (int)(GetTime() * 1000.0);
	particle->maxAge = maxAge;
	particle->zoom = 1.0f;
	particle->alpha = 1.0f;
	particle->updateFunc = updateFunc;
}
