#include "component.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA(ca, entity) ((char*)ca->data + entity * ca->component_size)

void init_component_array(ComponentArray* ca, size_t component_size) {
    ca->data = malloc(MAX_ENTITIES * component_size);
    ca->component_size = component_size;
    memset(ca->active, false, sizeof(ca->active));
}
void free_component_array(ComponentArray* ca) { 
    free(ca->data);
}
const void* get_component(const ComponentArray* ca, Entity entity) {
   return (void*)DATA(ca, entity);
}
void set_component(ComponentArray* ca, Entity entity, const void* ptr) {
    memcpy(DATA(ca, entity), ptr, ca->component_size);
    ca->active[entity] = true;
}
void log_transform_component(const TransformComponent* tc) {
	printf("TRANSFORM: x: %.2f y: %.2f w: %.2f h: %.2f r: %.2f\n", 
			tc->position.x, tc->position.y, tc->size.x, tc->size.y, tc->rotation);  
}
void log_jump_component(const JumpComponent* jc) {
	printf("JUMP: f: %.2f is: %d\n", jc->jump_force, jc->is_jumping);
}
void log_movement_component(const MovementComponent* mc) {
	printf("MOVEMENT: vx: %.2f vy: %.2f ax: %.2f ay: %.2f\n",
			mc->velocity.x, mc->velocity.y, mc->acceleration.x, mc->acceleration.y);
}
void init_component_manager(ComponentManager* cm) {
    INIT_COMP_ARRAY(&cm->transforms, TransformComponent);
    INIT_COMP_ARRAY(&cm->movements, MovementComponent);
}
void log_component_manager(const ComponentManager* cm) {
    for (int i = 0; i < MAX_ENTITIES; i += 1) {
        if (cm->transforms.active[i]) {
            const TransformComponent* transform = GET_COMP_PTR(&cm->transforms, i, TransformComponent);
            printf("%d", i);
			log_transform_component(transform);
        }
        if (cm->movements.active[i]) {
            const MovementComponent* movement = GET_COMP_PTR(&cm->movements, i, MovementComponent);
            printf("%d", i);
			log_movement_component(movement);
        }
	}
}
void free_component_manager(ComponentManager* cm) {
    free_component_array(cm->transforms.data);
    free_component_array(cm->movements.data);
}
