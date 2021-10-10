#include "scene.h"

static int current_scene;

Scene scenes[] = {
    (Scene) { NULL, { (u_int8_t)1, (u_int8_t)1, (u_int8_t)1, (u_int8_t)0, (u_int8_t)1 } }
};

void scene_load(const int id) 
{
    current_scene = id;

    if (scenes[id].enabled_systems[SYSTEM_ID_PLAYER]) 
    {
        player_init();
    }

    if (scenes[id].enabled_systems[SYSTEM_ID_METEORS])
    {
        meteors_init(textures_getTexture("meteor"));
    }
}

void scene_update()
{
    Scene *current = scene_getCurrentScene();

    if (current->enabled_systems[SYSTEM_ID_METEORS]) 
    {
        meteors_update(&current->entities);
    }

    //  TODO:   Rewamp this
    EntityListItem *tmp = current->entities;
    while (tmp != NULL)
    {
        if (tmp->item.components.transform != NULL)
        {
            if (current->enabled_systems[SYSTEM_ID_SPRITE]) 
            {
                if (tmp->item.components.sprite != NULL)
                    sprite_update(&tmp->item);
            }
            
            switch (tmp->item.type)
            {
                case player:
                    player_update(&tmp->item);
                    break;
                
                case meteor:
                    if (current->enabled_systems[SYSTEM_ID_METEORS])
                    {
                        EntityListItem *tmp1 = tmp->next;

                        if (meteors_updateEntity(&current->entities, &tmp->item))
                        {
                            tmp = tmp1;
                            continue;
                        }
                    }
                    break;
            }

            if (current->enabled_systems[SYSTEM_ID_RIGIDBODY])
            {
                if (tmp->item.components.rigidbody != NULL)
                    rigidbody_update(&tmp->item);
            }
        }
        
        tmp = tmp->next;
    }
}

Scene *scene_getCurrentScene() 
{
    return &scenes[current_scene];
}