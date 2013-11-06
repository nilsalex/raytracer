#include "trace/ray_tracer.hpp"

RayTracer::RayTracer(Scene *scene) {
  RayTracer::scene = scene;
}

RayTracer::~RayTracer(void) {}

bool RayTracer::RayTrace(Ray &ray, RGBColour &colour, double &t, double const& coef, int const& depth) {

  // Check for collisions

  Shape *object_hit;
  int hit = 0;

  int num_objects = scene->get_number_of_shapes();
  for (int i = 0; i < num_objects; i++) {
    Shape *shape = (Shape *)scene->objects[i];
    if (shape->Hit(ray, t)) {
      object_hit = (Shape *)scene->objects[i];
      hit = 1;
    }
  }

  // Nothing hit
  if (hit == 0) {
    return false;
  }

  Material *material = object_hit->get_material();

  colour = material->get_colour();

  fprintf(stdout, "%.2f, %.2f, %.2f\n", colour.get_red(), colour.get_green(), colour.get_blue());

  return true;
}
