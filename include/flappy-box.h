#ifndef FLAPPY_BOX_H
#define FLAPPY_BOX_H

#include <raylib.h>

typedef struct {
	Rectangle body;
	Vector2 velocity;
	float rotation;
} Box;


void run_flappy_box();

#endif
