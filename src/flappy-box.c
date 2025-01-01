#include "flappy-box.h"
#include "components.h"
#include "raylib.h"
#include <stdio.h>

#define GRAVITY 4.9f

void init_component_manager(ComponentManager* cm)
{
    INIT_COMP_ARRAY(&cm->positions, Vector2);
    INIT_COMP_ARRAY(&cm->sizes, Vector2);
    INIT_COMP_ARRAY(&cm->velocities, Vector2);
    INIT_COMP_ARRAY(&cm->accelerations, Vector2);
    INIT_COMP_ARRAY(&cm->rotations, float);
}
void log_component_manager(const ComponentManager* cm)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        if (cm->positions.active[i]) {
            const Vector2* position = GET_COMP_PTR(&cm->positions, i, Vector2);
            printf("POSITION #%d: x: %.2f, y: %.2f\n", i, position->x, position->y);
        }
        if (cm->sizes.active[i]) {
            const Vector2* size = GET_COMP_PTR(&cm->sizes, i, Vector2);
            printf("SIZE #%d: x: %.2f, y: %.2f\n", i, size->x, size->y);
        }
        if (cm->velocities.active[i]) {
            const Vector2* velocity = GET_COMP_PTR(&cm->velocities, i, Vector2);
            printf("VELOCITY #%d: x: %.2f, y: %.2f\n", i, velocity->x, velocity->y);
        }
        if (cm->accelerations.active[i]) {
            const Vector2* acceleration = GET_COMP_PTR(&cm->accelerations, i, Vector2);
            printf("ACCELERATION #%d: x: %.2f, y: %.2f\n", i, acceleration->x, acceleration->y);
        }
        if (cm->rotations.active[i]) {
            const float* rotation = GET_COMP_PTR(&cm->rotations, i, float);
            printf("ROTATION #%d: %.2f\n", i, *rotation);
        }
    }
}
void free_component_manager(ComponentManager* cm)
{
    free_component_array(cm->positions.data);
    free_component_array(cm->sizes.data);
    free_component_array(cm->velocities.data);
    free_component_array(cm->accelerations.data);
    free_component_array(cm->rotations.data);
}
void render_system(const ComponentManager* cm)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        // I am not planning to render a dot. Every object needs a size.
        if (!cm->positions.active[i] || !cm->sizes.active[i])
            continue;

        const Vector2* position = GET_COMP_PTR(&cm->positions, i, Vector2);
        const Vector2* size = GET_COMP_PTR(&cm->sizes, i, Vector2);
        Rectangle body = { position->x, position->y, size->x, size->y };

        if (cm->rotations.active[i]) {
            DrawRectanglePro(body, (Vector2) { 0, 0 }, *GET_COMP_PTR(&cm->rotations, i, float), WHITE);
        } else {
            DrawRectanglePro(body, (Vector2) { 0, 0 }, 0.f, WHITE);
        }
    }
}
void update_system(ComponentManager* cm)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        // Skip updating if the object has no velocity.
        // I will not update a object that I will not render.
        if (!cm->positions.active[i] || !cm->sizes.active[i] || !cm->velocities.active[i])
            continue;

        const Vector2* position = GET_COMP_PTR(&cm->positions, i, Vector2);
        const Vector2* velocity = GET_COMP_PTR(&cm->velocities, i, Vector2);

        Vector2 new_position = { position->x + velocity->x, position->y + velocity->y };
        set_component(&cm->positions, i, &new_position);

        if (cm->accelerations.active[i]) {
            const Vector2* acceleration = GET_COMP_PTR(&cm->accelerations, i, Vector2);

            Vector2 new_velocity = { velocity->x + acceleration->x, velocity->y + acceleration->y };
            set_component(&cm->velocities, i, &new_velocity);
        }
    }
}
void run_flappy_box()
{
    ComponentManager cm;
    init_component_manager(&cm);

    // Create box
    Entity box = create_entity();
    SET_COMP(&cm.positions, box, Vector2, { 0.f, 0.f });
	SET_COMP(&cm.sizes, box, Vector2, { 20.f, 20.f });
    SET_COMP(&cm.velocities, box, Vector2, { 0.f, 0.f });
    SET_COMP(&cm.accelerations, box, Vector2, { 0.f, GRAVITY });
    SET_COMP(&cm.rotations, box, float, { 0.f });

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
