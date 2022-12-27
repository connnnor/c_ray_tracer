#include <stdlib.h> //getenv, atoi
#include <stdio.h>
#include "vec3.h"

#define IMG_WIDTH  256
#define IMG_HEIGHT 256

void write_color(vec3_s in) {
    int ir = (255.999 * in.e[0]);
    int ig = (255.999 * in.e[1]);
    int ib = (255.999 * in.e[2]);
    printf("%d %d %d\n", ir, ig, ib);
}

int main() {
    printf("P3\n" "%d\t%d\n" "255\n", IMG_WIDTH, IMG_HEIGHT);
    for (int i = IMG_HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < IMG_HEIGHT; ++j) {
            double r = (j+0.0) / (IMG_WIDTH - 1.0);
            double g = (i+0.0) / (IMG_HEIGHT - 1.0);
            double b = 0.25;
            vec3_s *pixel_rgb = vec3_new(.e = {r, g, b});
            write_color(*pixel_rgb);
        }
    }
}
