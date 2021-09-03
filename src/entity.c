#include "entity.h"

int entity_count = 0;

Entity entity_create()
{
    static unsigned long next_id = 0;

    Entity entity;
    entity.id = next_id++;      //  TODO: make a new ID system
    
    Components components;
    components.transform = NULL;
    components.sprite = NULL;
    components.box_collider = NULL;
    components.circle_collider = NULL;
    components.rigidbody = NULL;

    entity.components = components;

    return entity;
}

void entity_addTransformComponent(Entity *entity, Vector2D position, float scale, double angle)
{
    entity->components.transform = malloc(sizeof(Transform));
    entity->components.transform->position = position;
    entity->components.transform->scale = scale;
    entity->components.transform->angle = angle;
}

void entity_addSpriteComponent(Entity *entity, SDL_Texture *texture, const int number_of_animations, const Size2D tile_size)
{
    Sprite sprite;
    sprite.texture = texture;
    sprite.animations = malloc(sizeof(Animation) * number_of_animations);
    sprite.number_of_animations = number_of_animations;
    sprite.current_animation = 0;
    sprite.tile_size = tile_size;
    
    entity->components.sprite = malloc(sizeof(Sprite));
    *entity->components.sprite = sprite;
}

void entity_addBoxColliderComponent(Entity *entity, const Vector2D center, const Size2D size)
{
    entity->components.box_collider = malloc(sizeof(BoxCollider));
    entity->components.box_collider->center = center;
    entity->components.box_collider->size = size;
}

void entity_addCircleColliderComponent(Entity *entity, const Vector2D center, const float radius)
{
    entity->components.circle_collider = malloc(sizeof(CircleCollider));
    entity->components.circle_collider->center = center;
    entity->components.circle_collider->radius = radius;
}

void entity_addRigidbodyComponent(Entity *entity)
{
    entity->components.rigidbody = malloc(sizeof(Rigidbody));
}

void entity_addToList(EntityList *list, const Entity entity)
{
    if (*list == NULL)
    {
        *list = malloc(sizeof(EntityListItem));
        (*list)->next = NULL;
        (*list)->prev = NULL;
        (*list)->item = entity;
    }
    else
    {
        EntityListItem *tmp = *list;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        EntityListItem *new = malloc(sizeof(EntityListItem));
        tmp->next = new;
        
        new->prev = tmp;
        new->next = NULL;
        new->item = entity;
    }

    entity_count++;
}

void entity_delete(EntityList *list, unsigned long id)
{
    if (*list == NULL)
    {
        fprintf(stderr, "[Engine] Error deleting Entity: Entity list is empty!\n");
    }
    else
    {
        EntityListItem *tmp = *list;
        while (tmp != NULL && tmp->item.id != id)
        {
            tmp = tmp->next;
        }


        if (tmp == NULL)
        {
            fprintf(stderr, "[Engine] Erorr deleting Entity: Entity is not in the list!\n");
        }
        else
        {
            if (tmp->prev != NULL)
                tmp->prev->next = tmp->next;
            if (tmp->next != NULL)
                tmp->next->prev = tmp->prev;

            if (tmp->item.components.transform != NULL)
            {
                free(tmp->item.components.transform);
                tmp->item.components.transform = NULL;
            }

            if (tmp->item.components.sprite != NULL)
            {
                for (int i = 0; i < tmp->item.components.sprite->number_of_animations; i++)
                {
                    free(tmp->item.components.sprite->animations[i].frames);
                }
                free(tmp->item.components.sprite->animations);
                free(tmp->item.components.sprite);
                tmp->item.components.sprite = NULL;
            }

            if (tmp->item.components.box_collider != NULL)
            {
                free(tmp->item.components.box_collider);
                tmp->item.components.box_collider = NULL;
            }

            if (tmp->item.components.circle_collider != NULL)
            {
                free(tmp->item.components.circle_collider);
                tmp->item.components.circle_collider = NULL;
            }

            if (tmp->item.components.rigidbody != NULL)
            {
                free(tmp->item.components.rigidbody);
                tmp->item.components.rigidbody = NULL;
            }
            
            if (id == (*list)->item.id)
            {
                *list = (*list)->next;
                free(tmp);
            }
            else 
            {
                free(tmp);
            }
        }

        entity_count--;
    }
}