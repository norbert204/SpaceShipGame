#include "systems/system_player.h"

void player_update(Entity *entity)
{
    entity->components.rigidbody->velocity = (Vector2D) { keyboard_getAxisX(), keyboard_getAxisY() };
}