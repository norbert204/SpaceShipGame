#include "transform.h"

Vector2D vector2D_zero()
{
    Vector2D tmp = { 0, 0 };
    return tmp;
}

Transform transform_zero()
{
    return (Transform) { vector2D_zero(), 1, 0 };
}