#ifndef FLAPPY_BOX_H
#define FLAPPY_BOX_H

#include "component.h"

Entity create_box(ComponentManager* cm);

void render_system(const ComponentManager* cm);
void update_system(ComponentManager* cm);
void input_system(const ComponentManager* cm);

void run_flappy_box();

#endif
