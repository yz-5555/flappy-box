#include "components.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define data(entity) ((char*)component_array->data + entity * component_array->component_size)

void init_component_array(ComponentArray* component_array, size_t component_size)
{
    component_array->data = malloc(MAX_ENTITIES * component_size);
    component_array->component_size = component_size;
    memset(component_array->active, false, sizeof(component_array->active));
}
void free_component_array(ComponentArray* component_array)
{
	free(component_array->data);
}
const void* get_component(const ComponentArray* component_array, Entity entity)
{
    return (void*)data(entity);
}
void set_component(ComponentArray* component_array, Entity entity, const void* ptr)
{
    memcpy(data(entity), ptr, component_array->component_size);
    component_array->active[entity] = true;
}
