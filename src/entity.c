#include "entity.h"

Entity entity_create()
{
    Entity tmp;
    static int id = 0;
    
    tmp.id = id;
    tmp.transform = NULL;
    tmp.sprite = NULL;
    tmp.box_collider = NULL;
    tmp.circle_collider = NULL;

    id++;

    return tmp;
}

void entity_add(EntityList *list, Entity entity)
{
    if (*list == NULL)
    {
        *list = (EntityList)malloc(sizeof(EntityListItem));
        (*list)->prev = NULL;
        (*list)->next = NULL;
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
}

void entity_delete(EntityList list, int id)
{
    EntityListItem *tmp = list;
    while (tmp->item.id != id && tmp != NULL)
    {
        tmp = tmp->next;
    }

    if (tmp != NULL)
    {
        if (tmp->prev != NULL)
            tmp->prev->next = tmp->next;
        if (tmp->next != NULL)
            tmp->next->prev = tmp->prev;

        free(tmp);
    }
}

void *entity_clear(EntityList list)
{
    EntityListItem *tmp = list;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    while (tmp->prev != NULL)
    {
        tmp = tmp->prev;
        free(tmp->next);
        tmp->next = NULL;
    }

    free(list);

    return NULL;
}