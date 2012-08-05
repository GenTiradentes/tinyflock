#ifndef FLOCK_H_
#define FLOCK_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "vector.h"
#include "configuration.h"

typedef struct
{
	vector* location;
	vector* velocity;
	vector* acceleration;
} flock;

flock* flock_create(configuration* config);
void flock_destroy(flock* f);

void flock_randomize(flock* f, int start, int end);

typedef struct { int* run; int* frame_count; int* update_count; } status_args;
int status_thread(void* arg);

typedef struct { int thread_id; flock* f; configuration* config; vector* cursor_pos; int* cursor_interaction; } flock_update_worker_args;
int flock_update_worker_thread(void* arg);

// Update the location and velocity of each boid in the flock
typedef struct { int* run; flock* f; configuration* config; vector* cursor_pos; int* cursor_interaction; int* update_count; } flock_update_args;
int flock_update_thread(void* arg);

void flock_influence(vector* v, flock* f, int boid_id, configuration* config);

void boid_approach(flock* f, int boid_id, vector* v, float weight);
void boid_flee(flock* f, int boid_id, vector* v, float weight);

float rand_range(float min, float max);

#endif
