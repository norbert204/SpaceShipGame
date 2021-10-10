#include "engine/time.h"

static float delta_time;

void time_setDeltaTime(float time) 
{
    delta_time = time;
}

float time_getDeltaTime() 
{
    return delta_time;
}