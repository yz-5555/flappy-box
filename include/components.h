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

void init_component_array(ComponentArray* ca, size_t component_size);
#define INIT_COMP_ARRAY(ca_ptr, T) init_component_array(ca_ptr, sizeof(T))
void free_component_array(ComponentArray* dca);

const void* get_component(const ComponentArray* ca, Entity entity);
#define GET_COMP_PTR(ca_ptr, entity, T) (const T*)get_component(ca_ptr, entity)

void set_component(ComponentArray* ca, Entity entity, const void* ptr);
#define SET_COMP(ca_ptr, entity, T, ...) set_component(ca_ptr, entity, &(T)__VA_ARGS__)

#endif
