#include "rt_utils.h"
#include <stdlib.h>

double rand_double() {
    // return a random real in [0,1]
	return rand() / (RAND_MAX + 1.0);
}

double rand_double_in(double min, double max) {
    // return a random real in [min,max]
	return min + (max - min) * rand_double();
}

double clamp(double v, double min, double max) {
	if (v < min) { return min; }
	if (v > max) { return max; }
	return v;
}
