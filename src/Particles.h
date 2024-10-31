#ifndef PARTICLES_H
#define PARTICLES_H

#include "Vector.h"
#include <raylib.h>
#include <stdbool.h>

typedef struct Particle Particle;

typedef void (*ParticleFunc)(Particle*, float);

typedef struct Particle {
	bool used;
	Vector position;
	Vector speed;
	Vector acceleration;
	int creationTime;
	int maxAge;
	float zoom;
	float alpha;
	ParticleFunc updateFunc;
} Particle;

void particlesReset();
void particlesUpdate(float frameTime);
void particlesRender();
void particleCreate(Vector position, Vector speed, Vector acceleration, int maxAge, ParticleFunc updateFunc);

#endif