P=raytracer
OBJECTS=vec3.o ray.o hittable.o rt_utils.o camera.o
#CFLAGS=-g -Wall -O3 -Wno-initializer-overrides -std=c99 -lm
# debug flags
CFLAGS=-g -Wall -O0 -Wno-initializer-overrides -std=c99 -lm -gdwarf-4 -pg
LDLIBDS=
CC=clang

$(P): $(OBJECTS)

.PHONY : clean
clean:
	rm -f $(OBJECTS) $(P)
