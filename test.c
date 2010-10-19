#include "include/gravity.h"
#include "include/particle.h"
#include <stdio.h>
#include <stdlib.h>

vector_t sun_pos = { .x = 0, .y = 0, .z = 0};
vector_t sun_vel = { .x = 0, .y = 0, .z = 0};

vector_t earth_pos = { .x = AU, .y = 0, .z = 0};
vector_t earth_vel = { .x = 0, .y = EARTH_SPEED, .z = 0};

particle_t sun, earth;
particle_t sun_t, earth_t;

int main(int argc, char *argv[])
{
     double dt, r, v;
     int i;

     set_gravity(GRAVITY_FACTOR);
     
     sun = particle_create(sun_pos, sun_vel, SOLAR_MASS, get_radius_calc());
     earth = particle_create(earth_pos, earth_vel, EARTH_MASS, get_radius_calc());
     
     dt = 20.0;
     r = vector_length(&earth_pos);
     printf("Initial distance = %g\n", r / AU);
     
     for (i = 0; i < 3 * dt * dt * 24 * 365; i++) {
          vector_t force = gravitation(&sun, &earth);
          vector_t pos;
          integrate(&earth_t, &earth, force, dt);
          vector_scale(&force, -1);
          integrate(&sun_t, &sun, force, dt);
          sun = sun_t;
          earth = earth_t;
          pos = earth.position;
          if (i % (int) (dt * dt * 24) == 0) {
               vector_sub(&pos, &sun.position);
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

     
