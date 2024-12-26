#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <raylib.h>
#include <stdbool.h>

#include "entity.h"

typedef struct {
    void* data;
    size_t component_size;
    bool active[MAX_ENTITIES];
} ComponentArray;

void init_component_array(ComponentArray* component_array, size_t component_size);
#define INIT_C_ARRAY(ca_ptr, T) init_component_array(ca_ptr, sizeof(T))
void free_component_array(ComponentArray* component_array);

const void* get_component(const ComponentArray* component_array, Entity entity);
#define GET_C_PTR(ca_ptr, entity, T) (const T*)get_component(ca_ptr, entity)

void set_component(ComponentArray* component_array, Entity entity, const void* ptr);
#define SET_C(ca_ptr, entity, T, ...) set_component(ca_ptr, entity, &(T)__VA_ARGS__)

#endif
