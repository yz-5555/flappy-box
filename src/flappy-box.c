#include "flappy-box.h"
#include "component.h"
#include "raylib.h"
#include <stdio.h>

#define GRAVITY 4.9f

Entity create_box(ComponentManager* cm) {
    Entity box = create_entity();
    SET_COMP(&cm->positions, box, Vector2, {0.f, 0.f});
    SET_COMP(&cm->sizes, box, Vector2, {20.f, 20.f});
    SET_COMP(&cm->velocities, box, Vector2, {0.f, 0.f});
    SET_COMP(&cm->accelerations, box, Vector2, {0.f, GRAVITY});
    SET_COMP(&cm->rotations, box, float, {0.f});

    return box;
}
void render_system(const ComponentManager* cm) {
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        // I am not planning to render a dot. Every object needs a size.
        if (!cm->positions.active[i] || !cm->sizes.active[i])
            continue;

        const Vector2* position = GET_COMP_PTR(&cm->positions, i, Vector2);
        const Vector2* size = GET_COMP_PTR(&cm->sizes, i, Vector2);
        Rectangle body = {position->x, position->y, size->x, size->y};

        if (cm->rotations.active[i]) {
            DrawRectanglePro(body, (Vector2){0, 0},
                             *GET_COMP_PTR(&cm->rotations, i, float), WHITE);
        } else {
            DrawRectanglePro(body, (Vector2){0, 0}, 0.f, WHITE);
        }
    }
}
void update_system(ComponentManager* cm) {
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        // Skip updating if the object has no velocity.
        // I will not update a object that I will not render.
        if (!cm->positions.active[i] || !cm->sizes.active[i] ||
            !cm->velocities.active[i])
            continue;

        const Vector2* position = GET_COMP_PTR(&cm->positions, i, Vector2);
        const Vector2* velocity = GET_COMP_PTR(&cm->velocities, i, Vector2);

        Vector2 new_position = {position->x + velocity->x,
                                position->y + velocity->y};
        set_component(&cm->positions, i, &new_position);

        if (cm->accelerations.active[i]) {
            const Vector2* acceleration =
                GET_COMP_PTR(&cm->accelerations, i, Vector2);

            Vector2 new_velocity = {velocity->x + acceleration->x,
                                    velocity->y + acceleration->y};
            set_component(&cm->velocities, i, &new_velocity);
        }
    }
}
void run_flappy_box() {
    ComponentManager cm;
    init_component_manager(&cm);

    // Create box
    Entity box = create_box(&cm);

    log_component_manage(&cm);

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
