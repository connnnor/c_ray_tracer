# c ray tracer

I'm reading through [Ray Tracing in One Weekend][1] and implementing it in C99. 
Skipping some parts.

__Running__:

Program outputs scene in ppm format to stdout, so the easiest way to view is 
by redirecting to file `image.ppm`, then opening that in your image viewer

```
# compile
make clean && make
# write output to file
./raytracer > image.ppm
```

[1]: https://raytracing.github.io/books/RayTracingInOneWeekend.html
