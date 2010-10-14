#include "include/particle.h"

void
vector_add(vector_t *dst, vector_t *src)
{
     dst->x += src->x;
     dst->y += src->y;
     dst->z += src->z;
}

void
vector_scale(vector_t *dst, double factor)
{
     dst->x *= factor;
     dst->y *= factor;
     dst->z *= factor;
}


particle_t
mass_center(particle_t *particles, unsigned amount)
{
     particle_t result;
     vector_t position;
     unsigned i;
     
     for (i = 0; i < amount; i++) 
	  result.mass += particles[i].mass;

     for (i = 0; i < amount; i++) {
	  double weight = particles[i].mass / result.mass;
	  vector_t tmp = particles[i].position;
	  vector_scale(tmp, weight);
	  vector_add(&particles.position, &tmp);
     }
     return result;
}

	  
