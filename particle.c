#include "include/particle.h"

double
radius(double mass) 
{
     /* V = 4 PI V / 3
      * r ^ 3 = (4V / 3PI)
      */
     double volume = mass / MASS_DENSITY;
     return pow((4.0 / (3.0 * M_PI)) * volume, 1.0 / 3.0);
}

static radius_calc calc_radius = radius;

radius_calc get_radius_calc(void)
{
     return calc_radius;
}

void set_radius_calc(radius_calc calc)
{
     calc_radius = calc;
}

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

void
vector_sub(vector_t *dst, vector_t *src)
{
     vector_t tmp = *src;
     vector_scale(&tmp, -1);
     vector_add(dst, &tmp);
}

void
vector_normalize(vector_t *dst)
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
	  vector_add(&result.position, &tmp);
     }
     return result;
}

particle_t
particle_create(vector_t pos, vector_t vel, double mass, radius_calc f)
{
     particle_t result = {
	  .position = pos,
	  .velocity = vel,
	  .mass = mass,
	  .radius = log(mass)
     };
     if (f)
	  result.radius = f(mass);
     return result;
}

particle_t
particle_merge(particle_t *p1, particle_t *p2)
{
     double mass = p1->mass + p2->mass;
     vector_t pos, vel;

     /* FIXME: This could be cleverer. */
     pos.x = (p1->position.x * p1->mass + p2->position.x * p2->mass) / mass;
     pos.y = (p1->position.y * p1->mass + p2->position.y * p2->mass) / mass;
     pos.z = (p1->position.z * p1->mass + p2->position.z * p2->mass) / mass;

     vel.x = (p1->velocity.x * p1->mass + p2->velocity.x * p2->mass) / mass;
     vel.y = (p1->velocity.y * p1->mass + p2->velocity.y * p2->mass) / mass;
     vel.z = (p1->velocity.z * p1->mass + p2->velocity.z * p2->mass) / mass;

     return particle_create(pos, vel, mass, calc_radius);
}

void
particle_sprint(particle_t *p, char *buf)
{
     /* FIXME: Should be able to scale by light years or AUs or whatever */
     sprintf(buf, "<[Mass %g, Radius %g] pos = [%g, %g, %g] v = [%g, %g, %g]>",
	     p->mass, p->radius, p->position.x, p->position.y, p->position.z,
	     p->velocity.x, p->velocity.y, p->velocity.z);
}

void
particle_print(particle_t *p, FILE *fp)
{
     char buf[256];
     particle_sprint(p, buf);
     fprintf(fp, "%s", buf);
}
