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
#include "engine/time.h"
#include "engine/inputs.h"
#include "engine/textures.h"

#include "entity.h"

#include "systems/system_player.h"
#include "systems/system_sprite.h"
#include "systems/system_rigidbody.h"
#include "systems/system_meteors.h"
#include "background.h"

#include "scene.h"

char working_directory[FILENAME_MAX];

#define MIN_FRAME_TIME 1000
#define UPDATE_DELAY 10

bool stop = false;

Settings settings;

void handle_events(SDL_Event *event)
{
    while (SDL_PollEvent(event) != 0)
    {
        switch (event->type)
        {
            case SDL_QUIT:
                stop = true;
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

    int update_delay = UPDATE_DELAY;

    while (!stop)
    {
        frame_time = SDL_GetTicks();
        time_setDeltaTime(((float)frame_time - (float)last_frame) / 1000);
        //
        //  Handle events
        //
        handle_events(&event);

        //
        //  Update
        //  If we don't delay them we get some pretty weird bugs for some reason
        //
        if (update_delay == 0)
        {
            keyboard_update();
            background_update();
            scene_update();
        }
        else
        {
            update_delay--;
        }

        //
        //  Render
        //
        window_clear();
        
        //  Background Layer
        background_render();
       
        //  Sprite Layer
        sprite_render(scene_getCurrentScene()->entities);

        //  HUD Layer

        
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
    textures_load("res/bigrock.png", "meteor");
    textures_load("res/ship.png", "ship");
    textures_load("res/back.png", "background");
}

void stop_game()
{
    textures_destroy();
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
        
        settings_load(&settings, working_directory);
        load_textures();

        background_init(textures_getTexture("background"));

        scene_load(0);

        loop();
    }

    stop_game();

    return 0;
}
