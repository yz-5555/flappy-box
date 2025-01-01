#include "components.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA(ca, entity) ((char*)ca->data + entity * ca->component_size)

void init_component_array(ComponentArray* ca, size_t component_size)
{
    ca->data = malloc(MAX_ENTITIES * component_size);
    ca->component_size = component_size;
    memset(ca->active, false, sizeof(ca->active));
}
void free_component_array(ComponentArray* ca)
{
	free(ca->data);
}
const void* get_component(const ComponentArray* ca, Entity entity)
{
    return (void*)DATA(ca, entity);
}
void set_component(ComponentArray* ca, Entity entity, const void* ptr)
{
    memcpy(DATA(ca, entity), ptr, ca->component_size);
    ca->active[entity] = true;
}
