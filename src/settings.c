#include "settings.h"

//  TODO: refactor these functions

void settings_createFile(Settings *settings, char *file)
{
    FILE *fp = fopen(file, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "[Engine] Couldn't create %s file!\n", SETTINGS_FILE);
        return;
    }

    fprintf(fp, "[Options]\n");
    fprintf(fp, "maxfps=%d\n", window_getRefreshRate());
    fprintf(fp, "showfps=0\n");

    settings->max_fps = window_getRefreshRate();
    settings->show_fps = false;

    fclose(fp);
}

void settings_readFromFile(Settings *settings, FILE *file)
{
    bool error = false;

    const int line_size = 100;
    char line[line_size];
    fgets(line, line_size, file);

    fgets(line, line_size, file);
    char *p = strtok(line, "=");
    p = strtok(NULL, "=");
    settings->max_fps = atoi(p);
    if (settings->max_fps < 0)
    {
        fprintf(stderr, "[Engine] Max FPS can't be a negative number! Using unlocked FPS instead.\n");
        settings->max_fps = 0;
    }

    fgets(line, line_size, file);
    p = strtok(line, "=");
    p = strtok(NULL, "=");
    settings->show_fps = atoi(p);
}

void settings_load(Settings *settings, char *working_directory)
{
    char file[1000];
    strcpy(file, working_directory);
    strcat(file, SETTINGS_FILE);

    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "[Engine] %s file doesn't exist! Attempting to create %s...\n", SETTINGS_FILE, SETTINGS_FILE);
        settings_createFile(settings, file);
    }
    else
    {
        settings_readFromFile(settings, fp);
        fclose(fp);
    }
}