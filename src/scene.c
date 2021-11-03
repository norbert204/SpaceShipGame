#include "scene.h"

static int current_scene;

Scene scenes[] = {
    (Scene) { NULL, { 1, 1, 1, 1, 1 }, "res/sound/GameMusicLoop.ogg" }
};

void scene_load(const int id) 
{
    current_scene = id;

    if (scenes[id].enabled_systems[SYSTEM_ID_PLAYER]) 
    {
        player_init(&scenes[id].entities, textures_getTexture("ship"));
    }

    if (scenes[id].enabled_systems[SYSTEM_ID_METEORS])
    {
        meteors_init(textures_getTexture("meteor"));
    }

    sound_playMusic(scenes[id].music_file);
}

void scene_update()
{
    Scene *current = scene_getCurrentScene();

    if (current->enabled_systems[SYSTEM_ID_METEORS]) 
    {
        meteors_update(&current->entities);
    }

    //  Just because we didn't enable said system for the scene it doesn't mean the entities shouldn't be updated properly
    EntityListItem *tmp = current->entities;
    while (tmp != NULL)
    {
        if (tmp->item.components.transform != NULL)
        {
            if (tmp->item.components.sprite != NULL)
                sprite_update(&tmp->item);
            
            switch (tmp->item.type)
            {
                case player:
                    player_update(&tmp->item);
                    break;
                
                case meteor:
                    EntityListItem *tmp1 = tmp->next;

                    if (meteors_updateEntity(&current->entities, &tmp->item))
                    {
                        tmp = tmp1;
                        continue;
                    }
                    break;
            }

            if (tmp->item.components.rigidbody != NULL)
                rigidbody_update(&tmp->item);
        }
        
        tmp = tmp->next;
    }
}

Scene *scene_getCurrentScene() 
{
    return &scenes[current_scene];
}