#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>

#include "transform.h"
#include "sprite.h"
#include "collision.h"

typedef struct
{
    int id;

    Transform *transform;
    Sprite *sprite;
    BoxCollider *box_collider;
    CircleCollider *circle_collider;
} Entity;

typedef struct entityListItem
{
    struct entityListItem *prev;
    Entity item;
    struct entityListItem *next;
} EntityListItem;

typedef EntityListItem * EntityList;

Entity entity_create();
void entity_add(EntityList *list, Entity entity);
void entity_delete(EntityList *list, int id);
void *entity_clear(EntityList *list);

#endif