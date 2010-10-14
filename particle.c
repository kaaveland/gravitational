#include "include/particle.h"

void
vector_copy(vector_t *dst, vector_t *src)
{
     dst->x = src->x;
     dst->y = src->y;
     dst->z = src->z;
}

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

double
vector_length(vector_t *src)
{
     return sqrt(src->x * src->x + src->y * src->y + src->z * src->z);
}

void vector_sub(vector_t *dst, vector_t *src)
{
     vector_t tmp = *src;
     vector_scale(&tmp, -1);
     vector_add(dst, &tmp);
}

void vector_normalize(vector_t *dst)
{
     double len = vector_length(dst);
     vector_scale(dst, 1 / len);
}

int
particle_intersection(particle_t *p1, particle_t *p2)
{
     vector_t distance = p1->position;
     vector_sub(&distance, &p2->position);
     return p1->radius + p2->radius >= vector_length(&distance);
}

particle_t
mass_center(particle_t *particles, int amount, int skip)
{
     particle_t result;
     vector_t position;
     int i;
     
     for (i = 0; i < amount; i++) {
	  if (i == skip) continue;
	  result.mass += particles[i].mass;
     }
     for (i = 0; i < amount; i++) {
	  double weight = particles[i].mass / result.mass;
	  vector_t tmp = particles[i].position;
	  if (i == skip) continue;
	  vector_scale(&tmp, weight);
	  vector_add(&particles[i].position, &tmp);
     }
     return result;
}

	  
