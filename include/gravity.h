#ifndef GRAVITY_H
#define GRAVITY_H 1
#define GRAVITY_FACTOR 1.0

#include <math.h>
#include "particle.h"

/* F = G m1m2 / r ^ 2 */
vector_t gravitation(particle_t *src, particle_t *dst);
/* a = F / m */
void integrate(particle_t *dst, particle_t *src, vector_t force, double dt);

/* For outside use only */
void set_gravity(double factor);
double get_gravity(void);

#endif 
