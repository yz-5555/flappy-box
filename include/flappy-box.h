#ifndef FLAPPY_BOX_H
#define FLAPPY_BOX_H

#include "components.h"

typedef struct {
	ComponentArray positions; // Vector2
    ComponentArray sizes; // Vector2
    ComponentArray velocities; // Vector2
	ComponentArray accelerations; // Vector2
	ComponentArray rotations; // float
} ComponentManager;

void init_component_manager(ComponentManager* cm);
void log_component_manager(const ComponentManager* cm);
void free_component_manager(ComponentManager* cm);

void render_system(const ComponentManager* cm);
void update_system(ComponentManager* cm);

void run_flappy_box();

#endif
