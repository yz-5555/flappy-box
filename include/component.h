#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <raylib.h>
#include <stdbool.h>

#include "entity.h"

// Array that contains Component structs with dynamic allocation.
typedef struct {
    void* data;
    size_t component_size;
    bool active[MAX_ENTITIES];
} ComponentArray;

void init_component_array(ComponentArray* ca, size_t component_size);
#define INIT_COMP_ARRAY(ca_ptr, T) init_component_array(ca_ptr, sizeof(T))
void free_component_array(ComponentArray* ca);

const void* get_component(const ComponentArray* ca, Entity entity);
#define GET_COMP_PTR(ca_ptr, entity, T) (const T*)get_component(ca_ptr, entity)

void set_component(ComponentArray* ca, Entity entity, const void* ptr);
#define SET_COMP(ca_ptr, entity, T, ...) set_component(ca_ptr, entity, &(T)__VA_ARGS__)

// Components for flappy-box
typedef struct {
	Vector2 position;
	Vector2 size;
	float rotation;
} TransformComponent;
void log_transform_component(const TransformComponent* tc);

typedef struct {
	float jump_force;
	bool is_jumping;
} JumpComponent;
void log_jump_component(const JumpComponent* jc);

typedef struct {
	Vector2 velocity;
	Vector2 acceleration;
} MovementComponent;
void log_movement_component(const MovementComponent* mc);

// ComponentArrays for flappy-box
typedef struct {
	ComponentArray transforms;
	ComponentArray movements;
} ComponentManager;

void init_component_manager(ComponentManager* cm);
void log_component_manager(const ComponentManager* cm);
void free_component_manager(ComponentManager* cm);

#endif
