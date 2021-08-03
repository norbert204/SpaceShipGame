#include "systems/system_rigidbody.h"

void rigidbody_update(Entity *entity)
{
    entity->components.transform->position.x += entity->components.rigidbody->velocity.x * entity->components.rigidbody->speed * delta_time;
    entity->components.transform->position.y += entity->components.rigidbody->velocity.y * entity->components.rigidbody->speed * delta_time;
}