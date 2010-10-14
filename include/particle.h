#ifndef PARTICLE_H
#define PARTICLE_H 1

typedef struct vector 
{
     double x, y, z;
} vector_t;

struct particle
{
     vector_t position;
     vector_t velocity;
     
     double mass;
     double radius;
} particle_t;


/* In-place vector addition: vector_add(v1, v2) -> v1 += v2 */
void vector_add(vector_t *, vector_t *);
void vector_scale(vector_t *, double);

/* Find the center of mass of particles.
 * This means creating a particle at the weighted (by mass) average
 * position, with a mass equal to the sum of masses in particles */
particle_t mass_center(particle_t *, unsigned amount);

     
#endif
