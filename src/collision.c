#include "collision.h"

/*
    https://www.lazyfoo.net/tutorials/SDL/29_circular_collision_detection/index.php
*/

int colliding_circle_box(Transform a, Transform b, CircleCollider ac, BoxCollider bc)
{
    int cX, cY;

    int ax = a.position.x + ac.center.x;
    int bx = b.position.x + bc.center.x;

    int ay = a.position.y + ac.center.y;
    int by = b.position.y + bc.center.y;

    if (ax < bx - bc.size.w / 2)
    {
        cX = bx - bc.size.w / 2;
    }
    else if (ax > bx + bc.size.w / 2)
    {
        cX = bx + bc.size.w / 2;
    }
    else
    {
        cX = ax;
    }

    if (ay < by - bc.size.h / 2)
    {
        cY = by - bc.size.h / 2;
    }
    else if (ay > by + bc.size.h / 2)
    {
        cY = by + bc.size.h / 2;
    }
    else 
    {
        cY = ay;
    }

    int deltaX = cX - ax;
    int deltaY = cY - ay;

    if (deltaX*deltaX + deltaY*deltaY < ac.radius*ac.radius)
        return 1;
    
    return 0;
}