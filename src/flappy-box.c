#include "flappy-box.h"
#include <stdio.h>

void log_components(const Components* components)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        if (components->has_body[i]) {
            printf("BODY #%d: Rect x: %.2f, y: %.2f, w: %.2f, h: %.2f\n",
                i, components->bodies[i].x, components->bodies[i].y,
                components->bodies[i].width, components->bodies[i].height);
        }
        if (components->has_velocity[i]) {
            printf("VEL #%d: Vec2 x: %.2f, y: %.2f\n",
                i, components->velocities[i].x, components->velocities[i].y);
        }
        if (components->has_rotation[i]) {
            printf("ROT #%d: float %.2f\n", i, components->rotations[i]);
        }
    }
}
void init_components(Components* components)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        components->has_body[i] = false;
        components->has_velocity[i] = false;
        components->has_rotation[i] = false;
    }
}
Entity create_entity()
{
    static Entity next_id = 0;
    return next_id++;
}
int add_body(Components* components, Entity entity, float x, float y, float w, float h)
{
    if (entity >= MAX_ENTITIES) {
        fprintf(stderr, "Too many entities.\n");
        return 1;
    }

    components->bodies[entity] = (Rectangle) { x, y, w, h };
    components->has_body[entity] = true;

    return 0;
}
int add_velocity(Components* components, Entity entity, float x, float y)
{
    if (entity >= MAX_ENTITIES) {
        fprintf(stderr, "Too many entities.\n");
        return 1;
    }

    components->velocities[entity] = (Vector2) { x, y };
    components->has_velocity[entity] = true;

    return 0;
}
int add_rotation(Components* components, Entity entity, float rotation)
{
    if (entity >= MAX_ENTITIES) {
        fprintf(stderr, "Too many entites.\n");
        return 1;
    }

    components->rotations[entity] = rotation;
    components->has_rotation[entity] = true;

    return 0;
}
void render_system(const Components* components)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        if (!components->has_body[i])
            continue;

        if (components->has_rotation[i]) {
            DrawRectanglePro(components->bodies[i], (Vector2) { 0, 0 }, components->rotations[i], WHITE);
        } else {
            DrawRectanglePro(components->bodies[i], (Vector2) { 0, 0 }, 0.f, WHITE);
        }
    }
}
void update_system(Components* components)
{
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        if (!components->has_body[i])
            continue;

        if (components->has_velocity[i]) {
            components->bodies[i].x += components->velocities[i].x;
            components->bodies[i].y += components->velocities[i].y;
        }

        // TODO: rotation update
    }
}
int add_box(Components* components, Entity box)
{
    if (add_body(components, box, 0.f, 0.f, 20.f, 20.f) == 1) {
        fprintf(stderr, "add_box: Failed to add body\n");
        return 0;
    }
    if (add_velocity(components, box, 0.f, 0.f) == 1) {
        fprintf(stderr, "add_box: Failed to add velocity\n");
        return 1;
    }
    if (add_rotation(components, box, 0.f) == 1) {
        fprintf(stderr, "add_box: Failed to add rotation\n");
        return 1;
    }
    return 0;
}
void run_flappy_box()
{
    Components components;
    init_components(&components);

    // Create box
    Entity box = create_entity();
    if (add_box(&components, box) == 1) {
        fprintf(stderr, "run_flappy_box: Failed to add box\n");
        return;
    }

    log_components(&components);

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLUE);
			render_system(&components);
        }
        EndDrawing();

		update_system(&components);
    }
}
