#ifndef SYSTEM_COLLISION_H
#define SYSTEM_COLLISION_H

#include "../components/component_transform.h"
#include "../components/component_collider.h"

int colliding_circle_box(Transform a, Transform b, CircleCollider ac, BoxCollider bc);
int colliding_circle_circle(Transform a, Transform b, CircleCollider ac, CircleCollider bc);

#endif