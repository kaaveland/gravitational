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
      * v = v0 + dt * a = v0 + dt (m sum(r ^ 2 / (G m mi)) */
     vector_t acceleration;
     double F, a;

     dst->position = src->position;
     dst->mass = src->mass;
     dst->radius = src->radius;
     dst->velocity = src->velocity;
     
     F = vector_length(&force);
     a = F / src->mass;
     vector_copy(&acceleration, &force);
     vector_normalize(&acceleration);
     vector_scale(&acceleration, a); /* Acceleration vector */
     vector_scale(&acceleration, dt); /* Difference in velocity */

     vector_add(&dst->velocity, &acceleration); 
     vector_copy(&acceleration, &dst->velocity); /* Velocity vector */
     vector_scale(&acceleration, dt); /* Difference in position */
     vector_add(&dst->position, &acceleration);

}
