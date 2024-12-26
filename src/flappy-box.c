#include "flappy-box.h"
#include "components.h"
#include "raylib.h"
#include <stdio.h>

#define GRAVITY 4.9f

void init_component_manager(ComponentManager* cm)
{
    INIT_C_ARRAY(&cm->bodies, Rectangle);
    INIT_C_ARRAY(&cm->velocities, Vector2);
	INIT_C_ARRAY(&cm->accelerations, Vector2);
    INIT_C_ARRAY(&cm->rotations, float);
}
void log_component_manager(const ComponentManager* cm)
{
	for (int i = 0; i < MAX_ENTITIES; i += 1) {
		if (cm->bodies.active[i]) {
			const Rectangle* body = GET_C_PTR(&cm->bodies, i, Rectangle);
			printf("BODY #%d: x: %.2f, y: %.2f, w: %.2f, h: %.2f\n", i, body->x, body->y, body->width, body->height);
		}
		if (cm->velocities.active[i]) {
			const Vector2* velocity = GET_C_PTR(&cm->velocities, i, Vector2);
			printf("VELOCITY #%d: x: %.2f, y: %.2f\n", i, velocity->x, velocity->y);
		}
		if (cm->accelerations.active[i]) {
			const Vector2* acceleration = GET_C_PTR(&cm->accelerations, i, Vector2);
			printf("ACCELERATION #%d: x: %.2f, y: %.2f\n", i, acceleration->x, acceleration->y);
		}
		if (cm->rotations.active[i]) {
			const float* rotation = GET_C_PTR(&cm->rotations, i, float);
			printf("ROTATION #%d: %.2f\n", i, *rotation);
		}
	}
}
void free_component_manager(ComponentManager* cm)
{
	free_component_array(cm->bodies.data);
	free_component_array(cm->velocities.data);
	free_component_array(cm->accelerations.data);
	free_component_array(cm->rotations.data);
}
void render_system(const ComponentManager* cm)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        if (!cm->bodies.active[i])
            continue;

        if (cm->rotations.active[i]) {
            DrawRectanglePro(*GET_C_PTR(&cm->bodies, i, Rectangle), (Vector2) { 0, 0 }, *GET_C_PTR(&cm->rotations, i, float), WHITE);
        } else {
            DrawRectanglePro(*GET_C_PTR(&cm->bodies, i, Rectangle), (Vector2) { 0, 0 }, 0.f, WHITE);
        }
    }
}
void update_system(ComponentManager* cm)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        if (!cm->bodies.active[i])
            continue;

        if (!cm->velocities.active[i])
            continue;

        const Rectangle* body = GET_C_PTR(&cm->bodies, i, Rectangle);
		const Vector2* velocity = GET_C_PTR(&cm->velocities, i, Vector2);
		const Vector2* acceleration = GET_C_PTR(&cm->accelerations, i, Vector2);

		SET_C(&cm->bodies, i, Rectangle, { body->x + velocity->x, body->y + velocity->y, body->width, body->height }); 
		SET_C(&cm->velocities, i, Vector2, { velocity->x + acceleration->x, velocity->y + acceleration->y });
	}
}
void run_flappy_box()
{
    ComponentManager cm;
    init_component_manager(&cm);

    // Create box
    Entity box = create_entity();
    SET_C(&cm.bodies, box, Rectangle, { 0.f, 0.f, 20.f, 20.f });
	SET_C(&cm.velocities, box, Vector2, { 0.f, 0.f });
	SET_C(&cm.accelerations, box, Vector2, { 0.f, GRAVITY });
	SET_C(&cm.rotations, box, float, { 0.f });

	log_component_manager(&cm);

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLUE);
            render_system(&cm);
        }
        EndDrawing();

        update_system(&cm);
    }

}
