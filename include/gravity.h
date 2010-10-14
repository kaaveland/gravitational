#ifndef GRAVITY_H
#define GRAVITY_H 1
#define GRAVITY_FACTOR 1.0

#include <math.h>
#include "particle.h"

/* F = G m1m2 / r ^ 2 */
vector_t gravitation(particle_t *src, particle_t *dst);
/* a = F / m */
vector_t acceleration(particle_t *, particle_t *);

/* For outside use only */
void set_gravity(double factor);
double get_gravity(void);

#endif 
