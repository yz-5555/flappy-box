#ifndef FLAPPY_BOX_H
#define FLAPPY_BOX_H

#include <raylib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_ENTITIES 100

typedef uint32_t Entity;

typedef struct {
	Rectangle bodies[MAX_ENTITIES];
	bool has_body[MAX_ENTITIES];

	Vector2 velocities[MAX_ENTITIES];
	bool has_velocity[MAX_ENTITIES];
	
	float rotations[MAX_ENTITIES];
	bool has_rotation[MAX_ENTITIES];
} Components;

void log_components(const Components* components);
void init_components(Components* components);

Entity create_entity();
int add_body(Components* components, Entity entity, float x, float y, float w, float h);
int add_velocity(Components* components, Entity entity, float x, float y);
int add_rotation(Components* components, Entity entity, float rotation);

void render_system(const Components* components);
void update_system(Components* components);

int add_box(Components* components, Entity box);
void run_flappy_box();

#endif
