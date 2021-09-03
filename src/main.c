#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#if defined(_WIN32) || defined(WIN32)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "engine/draw.h"
#include "engine/window.h"
#include "engine/settings.h"
#include "engine/utilities.h"
#include "engine/inputs.h"

#include "entity.h"

#include "systems/system_player.h"
#include "systems/system_sprite.h"
#include "systems/system_rigidbody.h"
#include "systems/system_meteors.h"
#include "background.h"

char working_directory[FILENAME_MAX];

#define MIN_FRAME_TIME 1000

bool stop = false;

Settings settings;

//  TODO: implement a proper texture manager
SDL_Texture *tex_blank = NULL;
SDL_Texture *tex_meteorite = NULL;
SDL_Texture *tex_ship = NULL;
SDL_Texture *tex_background = NULL;
SDL_Texture *tex_test = NULL;

//  Temporary
EntityList list;

void handle_events(SDL_Event *event)
{
    while (SDL_PollEvent(event) != 0)
    {
        switch (event->type)
        {
            case SDL_QUIT:
                stop = true;
                break;
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym)
                {
                    case SDLK_e:
                        EntityListItem *tmp = list;
                        while (tmp != NULL)
                        {
                            printf("Entity %d:\n", tmp->item.id);
                            printf("\tType: %d\n", tmp->item.type);
                            printf("\tTransform: %s\n", (tmp->item.components.transform != NULL) ? "yes" : "no");
                            printf("\tSprite: %s\n", (tmp->item.components.sprite != NULL) ? "yes" : "no");
                            printf("\tBoxCollider: %s\n",  (tmp->item.components.box_collider != NULL) ? "yes" : "no");
                            printf("\tCircleCollider: %s\n",  (tmp->item.components.circle_collider != NULL) ? "yes" : "no");
                            printf("\tRigidbody: %s\n",  (tmp->item.components.rigidbody != NULL) ? "yes" : "no");

                            tmp = tmp->next;
                        }
                        printf("\n");
                        break;
                    case SDLK_d:
                        if (list != NULL)
                        {
                            EntityListItem *tmp = list;
                            while (tmp->next != NULL)
                            {
                                tmp = tmp->next;
                            }
                            while (tmp != NULL)
                            {
                                if (tmp->prev != NULL)
                                {
                                    tmp = tmp->prev;
                                    entity_delete(&list, tmp->next->item.id);
                                }
                                else 
                                {
                                    entity_delete(&list, tmp->item.id);
                                    tmp = NULL;
                                }
                            }
                        }
                        break;
                }
                break;
        }
    }
}

void loop()
{
    SDL_Event event;

    int frame_time;
    int last_frame;

    int fps = 0;
    int last_fps_calculation = SDL_GetTicks();

    //  If we don't delay the updates when starting the game, the background will be buggy
    int update_delay = 10;

    while (!stop)
    {
        frame_time = SDL_GetTicks();
        delta_time = ((float)frame_time - (float)last_frame) / 1000;
        //
        //  Handle events
        //
        handle_events(&event);

        //
        //  Update
        //
        keyboard_update();

        if (update_delay == 0)
        {
            //ship_update(&ship);
            background_update();
        }
        else
        {
            update_delay--;
        }

        //  TODO: move this to scene manager
        meteors_update(&list, tex_meteorite);

        EntityListItem *tmp = list;
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

                        if (meteors_updateEntity(&list, &tmp->item))
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

        //
        //  Render
        //
        window_clear();
        
        //  Background Layer
        background_render(tex_background);
       
        //  Sprite Layer
        sprite_render(list);

        //  HUD Layer
        //missile_renderHUD(tex_blank);

        window_display();

        //
        //  Delay to limit the FPS
        //
        if (settings.max_fps > 0) 
        {
            if (SDL_GetTicks() - frame_time < MIN_FRAME_TIME / settings.max_fps)
                SDL_Delay(MIN_FRAME_TIME  / settings.max_fps - (SDL_GetTicks() - frame_time));
        }
        
        last_frame = frame_time;

        //
        //  Wanna show FPS numbers?
        //
        if (settings.show_fps)
        {
            fps++;

            //  TODO: move this to window.h
            if (last_frame - last_fps_calculation > 1000)
            {
                last_fps_calculation = SDL_GetTicks();

                char title[100] = "SpaceShipGame - ";
                char fps_str[5];
                char entity_str[5];

                sprintf(fps_str, "%d", fps);
                sprintf(entity_str, "%d", entity_count);

                strcat(title, fps_str);
                strcat(title, " FPS | ");
                strcat(title, entity_str);
                strcat(title, " Entities");

                SDL_SetWindowTitle(window_getWindow(), title);

                fps = 0;
            }
        }
    }
}

void load_textures()
{
    tex_blank = window_loadTexture("res/blank.png");
    tex_meteorite = window_loadTexture("res/bigrock.png");
    tex_ship = window_loadTexture("res/ship.png");
    tex_background = window_loadTexture("res/back.png");
    tex_test = window_loadTexture("res/dio.png");
}

void destroy_textures()
{
    tex_blank = window_destroyTexture(tex_blank);
    tex_meteorite = window_destroyTexture(tex_meteorite);
    tex_ship = window_destroyTexture(tex_ship);
    tex_background = window_destroyTexture(tex_background);
    tex_test = window_destroyTexture(tex_background);
}

void stop_game()
{
    //TODO: move this from here
    //sprite_destroy(&ship.sprite);

    destroy_textures();
    window_stop();
}

void get_working_dir(char *executableName)
{
    if (executableName[0] == '/')
    {
        strcpy(working_directory, executableName);
    }
    else 
    {
        char tmp[FILENAME_MAX];
        GetCurrentDir(tmp, FILENAME_MAX);

        strcpy(working_directory, tmp);
        strcat(working_directory, "/");
        strcat(working_directory, executableName);
    }

    char *p;
    p = strrchr(working_directory, '/');
    *p = '\0';
    strcat(working_directory, "/");
}

int main(int argc, char* argv[])
{
    get_working_dir(argv[0]);

    if (window_init())
    {
        srand(time(NULL));
        
        list = NULL;

        settings_load(&settings, working_directory);
        load_textures();

        background_init();
        meteors_init();

        loop();
    }

    stop_game();

    return 0;
}
