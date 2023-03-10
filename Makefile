P=raytracer
OBJECTS=vec3.o ray.o hittable.o camera.o material.o
#CFLAGS=-g -Wall -O3 -Wno-initializer-overrides -std=c99 -lm
# debug flags
CFLAGS=-g3 -Wall -Wextra -O0 -Wno-initializer-overrides -std=c99 -lm -gdwarf-4
LDLIBDS=
CC=clang

$(P): $(OBJECTS)

.PHONY : clean
clean:
	rm -f $(OBJECTS) $(P)
