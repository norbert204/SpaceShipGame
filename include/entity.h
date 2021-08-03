#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdlib.h>

//  Components
#include "components/component_transform.h"
#include "components/component_sprite.h"
#include "components/component_collider.h"
#include "components/component_rigidbody.h"

//  https://prdeving.wordpress.com/2018/06/27/videogames-programming-ecs-system-in-plain-c/

enum EntityType
{
    player=0,
    meteor,
    missile,
};

//  I dont know if this is necessary
typedef struct
{
    Transform *transform;
    Sprite *sprite;
    BoxCollider *box_collider;
    CircleCollider *circle_collider;
    Rigidbody *rigidbody;
} Components;

typedef struct
{
    unsigned int id;
    enum EntityType type;
    Components components;
} Entity;

typedef struct entityListItem
{
    struct entityListItem *prev;
    Entity item;
    struct entityListItem *next;
} EntityListItem;

typedef EntityListItem * EntityList;

Entity entity_create();

void entity_addTransformComponent(Entity *entity, Vector2D position, float scale, double angle);
void entity_addSpriteComponent(Entity *entity, SDL_Texture *texture, const int number_of_animations, const Size2D tile_size);
void entity_addBoxColliderComponent(Entity *entity, const Vector2D center, const Size2D size);
void entity_addCircleColliderComponent(Entity *entity, const Vector2D center, const float radius);
void entity_addRigidbodyComponent(Entity *entity);

void entity_addToList(EntityList *list, const Entity entity);

void entity_delete(EntityList *list, Entity *entity);

#endif