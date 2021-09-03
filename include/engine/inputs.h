#ifndef INPUTS_H
#define INPUTS_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#define NUMBER_OF_KEYDOWN_EVENTS 322

void keyboard_init();
void keyboard_handleEvents(SDL_Event *event);
void keyboard_update();
bool keyboard_getKey(int scancode);
int keyboard_getAxisX();
int keyboard_getAxisY();

#endif