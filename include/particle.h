#ifndef PARTICLE_H
#define PARTICLE_H 1
#include <math.h>
#include <stdio.h>

typedef struct vector 
{
     double x, y, z;
} vector_t;

typedef struct particle
{
     vector_t position;
     vector_t velocity;
     
     double mass;
     double radius;
} particle_t;

typedef double (*radius_calc)(double);
radius_calc get_radius_calc(void);
void set_radius_calc(radius_calc);

void vector_copy(vector_t *dst, vector_t *src);
/* In-place vector addition: vector_add(v1, v2) -> v1 += v2 */
void vector_add(vector_t *dst, vector_t *src);
/* In-place vector subtraction: vector_sub(v1, v2) -> v1 -= v2 */
void vector_sub(vector_t *dst, vector_t *src);
/* In-place vector scaling: vector_scale(v1, f) -> v1 *= f */
void vector_scale(vector_t *dst, double factor);
/* In-place vector normalization */
void vector_normalize(vector_t *dst);
double vector_length(vector_t *src);

/* Find the center of mass of particles.
 * This means creating a particle at the weighted (by mass) average
 * position, with a mass equal to the sum of masses in particles.
 * We can skip one particle. If this is not desirable, pass a negative index.
 * This uses the fact that sum(mass x position) / particles -> center of gravity.
 * This pseudo-particle could in principle be used to calculate gravitational pull,
 * but it is only sufficiently accurate when distances are big (Even for celestial
 * objects). */
particle_t mass_center(particle_t *particles, int amount,  int skip);
/* Check if two particles intersect. When this happens, newtonian gravity
 * acts in strange ways, and we want to merge the particles. */
int particle_intersection(particle_t *p1, particle_t *p2);
/* Create a new particle */
particle_t particle_create(vector_t pos, vector_t vel, double mass, radius_calc f);
/* Merge two particles into one - call this if there's an intersection. */
particle_t particle_merge(particle_t *p1, particle_t *p2);
void particle_print(particle_t *p, FILE *fp);
void particle_sprint(particle_t *p, char *buf);
/* FIXME: implement n log n sorting of particles by distance from radius.
 * This allows n log n collision detection as we can only have collisions between
 * neighbours in this list, which means we can linearly check collisions and
 * the sorting becomes the dominant factor of the complexity. */
void particle_sort(particle_t *p, int amount);

#endif
