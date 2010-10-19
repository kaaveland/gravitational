#ifndef GRAVITY_H
#define GRAVITY_H 1
/* FIXME: Add some GRAVITY_* constants that allows user to work in
 * different units, eg: time -> year, distance -> au, speed -> au/year,
 * mass -> solar masses gives -> gravitational constant = 1. Others as well,
 * ie lightyears and so on. */
/* Useful constants */

#include <math.h>
#include "particle.h"

#define AU 149597871000.0 /* AU in meters */
#define YEAR_SECONDS 60.0 * 60.0 * 24.0 * 365.25 /* Seconds in a year */
#define LIGHT_YEAR 3E8 * YEAR_SECONDS /* Distance traveled by light in a year */
#define SOLAR_MASS 2E30 /* Solar mass in kgs */
#define EARTH_MASS 6E24 /* Earths mass in kgs */
#define EARTH_SPEED 29780 /* Average earth speed in m/s */
#define GRAVITY_FACTOR 6.67428E-11 /* Gravitational constant */

/* F = G m1m2 / r ^ 2 */
vector_t gravitation(particle_t *src, particle_t *dst);
/* a = F / m */
void integrate(particle_t *dst, particle_t *src, vector_t force, double dt);

/* For outside use only */
void set_gravity(double factor);
double get_gravity(void);

#endif 
