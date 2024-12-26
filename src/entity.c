#include "entity.h"

Entity create_entity()
{
	static Entity next_entity = 0;

	return next_entity++;
}
