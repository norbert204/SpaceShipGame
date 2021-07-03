#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "draw.h"
#include "window.h"
#include "settings.h"
#include "utilities.h"
#include "transform.h"
#include "ship.h"
#include "background.h"
#include "meteors.h"
#include "missile.h"

char working_directory[1000];

#define MIN_FRAME_TIME 1000

bool stop = false;

Settings settings;

SDL_Texture *tex_blank = NULL;
SDL_Texture *tex_meteorite = NULL;
SDL_Texture *tex_ship = NULL;
SDL_Texture *tex_background = NULL;

Ship ship;

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
                ship_handleEvent(&ship, event);
                missile_handleEvent(event, ship.transform.position);
                break;
            case SDL_KEYUP:
                ship_handleEvent(&ship, event);
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

    //  TODO: Move it to meteors.c
    float meteorSpawnTimer = 3;

    bool colliding = false;

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
        if (update_delay == 0)
        {
            ship_update(&ship);
            background_update();
            
            meteorSpawnTimer -= delta_time;
            if (meteorSpawnTimer < 0)
            {
                meteors_add();
                meteorSpawnTimer = .5f;
            }
            
            meteors_update();
            missile_update();

            //  TODO: move this from here
            for (int i = 0; i < meteors_top; i++)
            {
                colliding = colliding_circle_box(meteors[i].transform, ship.transform, meteors[i].collider, ship.collider);

                if (colliding)
                    break;
            }
        }
        else
        {
            update_delay--;
        }

        

        //
        //  Render
        //
        window_clear();
        //  Background
        background_render(tex_background);
        //  Sprites
        meteors_render(tex_meteorite, (Size2D) { 64, 64 });
        missile_render(tex_blank);
        ship_render(&ship, tex_ship);

        //draw_rectangle(ship.transform.position.x + ship.collider.center.x - ship.collider.size.w / 2, ship.transform.position.y + ship.collider.center.y - ship.collider.size.h / 2, ship.collider.size.w, ship.collider.size.h, (colliding) ? COLOR_RED : COLOR_WHITE);

        //  HUD
        missile_renderHUD(tex_blank);

        window_display();

        if (settings.max_fps > 0) 
        {
            if (SDL_GetTicks() - frame_time < MIN_FRAME_TIME / settings.max_fps)
                SDL_Delay(MIN_FRAME_TIME  / settings.max_fps - (SDL_GetTicks() - frame_time));
        }
        
        last_frame = frame_time;
        if (settings.show_fps)
        {
            fps++;

            //  TODO: move this to window.h
            if (last_frame - last_fps_calculation > 1000)
            {
                last_fps_calculation = SDL_GetTicks();

                char title[100] = "SpaceShipGame - ";
                char fps_str[5];

                sprintf(fps_str, "%d", fps);
                strcat(title, fps_str);
                strcat(title, " FPS");

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
}

void destroy_textures()
{
    tex_blank = window_destroyTexture(tex_blank);
    tex_meteorite = window_destroyTexture(tex_meteorite);
    tex_ship = window_destroyTexture(tex_ship);
    tex_background = window_destroyTexture(tex_background);
}

void stop_game()
{
    background_destroy();

    destroy_textures();
    window_stop();
}

int main(int argc, char* argv[])
{
    //  TODO:
    //  -   make a windows version of this
    //  -   move this from here

    if (argv[0][0] == '/')
    {
        strcpy(working_directory, argv[0]);
    }
    else 
    {
        char tmp[1000];
        getcwd(tmp, 1000);
        strcpy(working_directory, tmp);
        strcat(working_directory, "/");
        strcat(working_directory, argv[0]);
    }

    char *p;
    p = strrchr(working_directory, '/');
    *p = '\0';
    strcat(working_directory, "/");


    if (window_init())
    {
        srand(time(NULL));
        
        settings_load(&settings, working_directory);

        load_textures();
        
        background_init();
        ship_init(&ship);
        meteors_init();
        missile_init();

        loop();
    }

    stop_game();

    return 0;
}
