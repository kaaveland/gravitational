#ifndef GRAVITY_H
#define GRAVITY_H 1
#define GRAVITY_FACTOR 1

#include <math.h>
#include "particle.h"

/* F = G m1m2 / r ^ 2 */
vector_t gravitation(particle_t *, particle_t*);
/* a = F / m */
vector_t acceleration(particle_t *, particle_t *);
particle_t update(particle_t *, particle_t *);

#endif GRAVITY_H
