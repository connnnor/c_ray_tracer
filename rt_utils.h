#ifndef RTUTILS_H
#define RTUTILS_H
#include <stdlib.h>
//#include <math.h> // M_PI
#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif /* M_PI */
//static inline double rand_double();
//static inline double rand_double_in(double min, double max);
//static inline double clamp(double v, double min, double max);

static inline double rand_double() {
    // return a random real in [0,1]
	return rand() / (RAND_MAX + 1.0);
}

static inline double rand_double_in(double min, double max) {
    // return a random real in [min,max]
	return min + (max - min) * rand_double();
}

static inline double clamp(double v, double min, double max) {
	if (v < min) { return min; }
	if (v > max) { return max; }
	return v;
}

static inline double deg_to_rad(double d) {
    return d * M_PI / 180.0;
}
#endif
