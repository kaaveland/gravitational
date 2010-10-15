#include "include/gravity.h"

static double gravity = GRAVITY_FACTOR;

void
set_gravity(double factor)
{
     gravity = factor;
}

double
get_gravity(void)
{
     return gravity;
}

vector_t
gravitation(particle_t *src, particle_t *dst)
{
     vector_t force;
     double dist, mass, total_gravity;

     mass = src->mass * dst->mass;
     
     force = src->position;
     vector_sub(&force, &dst->position);

     dist = vector_length(&force);
     vector_normalize(&force);

     total_gravity = gravity * mass / (dist * dist);
     vector_scale(&force, total_gravity);
     
     return force;
}

void
integrate(particle_t *dst, particle_t *src, vector_t force, double dt)
{
     /* F = ma -> a = m / F 
      * int(a) -> v = (m / F) * a + v0
      */
     double factor = 1 / src->mass;
     vector_scale(&force, factor);
     
     
}
