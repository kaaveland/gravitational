#include "include/gravity.h"
#include "include/particle.h"
#include <stdio.h>
#include <stdlib.h>

/* Account for the Earths momentum - the sun should be moving in the opposite
 * direction with as much momentum as that of the Earth. The values for the Sun
 * are inferred only from induced forces from the Earth, in an attempt to
 * make sure the system has 0, 0, 0 as the center of mass. */
vector_t sun_pos = { .x = -AU / SOLAR_MASS * EARTH_MASS, .y = 0, .z = 0};
vector_t sun_vel = { .x = 0, .y = - EARTH_SPEED * EARTH_MASS / SOLAR_MASS, .z = 0};

vector_t earth_pos = { .x = AU * (1 - EARTH_MASS / SOLAR_MASS) , .y = 0, .z = 0};
vector_t earth_vel = { .x = 0, .y = EARTH_SPEED, .z = 0};

particle_t sun, earth;
particle_t sun_t, earth_t;

int main(int argc, char *argv[])
{
     double dt, r, v;
     int i; int ym = (int) YEAR_MINUTES;

     set_gravity(GRAVITY_FACTOR);
     sun = particle_create(sun_pos, sun_vel, SOLAR_MASS, get_radius_calc());
     earth = particle_create(earth_pos, earth_vel, EARTH_MASS, get_radius_calc());
     dt = 60.0; /* Time step is a minute */
     r = vector_length(&earth_pos);
     
     for (i = 0; i < 150 * YEAR_MINUTES; i++) { /* 150 years, a minute at a time */
          vector_t force = gravitation(&sun, &earth);
          vector_t tmp = force;
          integrate(&earth_t, &earth, force, dt);
               vector_scale(&tmp, -1);
               integrate(&sun_t, &sun, tmp, dt);
          sun = sun_t;
          earth = earth_t;
          if (i % ym == 0) { /* Every year */
               particle_print(&earth, stdout);
               putchar('\n');
               r = vector_length(&earth.position) + vector_length(&sun.position);
               v = vector_length(&earth.velocity);
               particle_print(&sun, stdout);
               printf("\nDistance is %gAU, velocity is %g\n", r / AU, v);
          }
     }
     return EXIT_SUCCESS;
}

     
