#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "window.h"

#define SETTINGS_FILE "settings.ini"

typedef struct
{
    int max_fps;
    bool show_fps;
} Settings;

void settings_createFile(Settings *settings, char *file);
void settings_readFromFile(Settings *settings, FILE *file);
void settings_load(Settings *settings, char *working_directory);

#endif