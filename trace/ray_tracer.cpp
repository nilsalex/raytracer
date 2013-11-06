#include "trace/ray_tracer.hpp"

RayTracer::RayTracer(Scene *scene) {
  RayTracer::scene = scene;
}

RayTracer::~RayTracer(void) {}

bool RayTracer::RayTrace(Ray &ray, RGBColour &colour, double &t, double const& coef, int const& depth) const {

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

#ifdef CASTING_ONLY
  colour = material->get_colour();
  return true;
#endif

  // Reflection
  Vector direction(ray.get_direction());
  reflect_(ray.hit_info.normal, direction);
  ray.set_direction(direction);

  Ray reflected_ray(ray.hit_info.position + ray.get_direction() * EPSILON, direction);
  double dot = reflected_ray.get_direction() * ray.get_direction();

  // Diffuse shading
  Light *light = scene->get_lights();
  for (int i = 0; i < scene->get_number_of_lights(); light++, i++) {
    direction = light->get_position() - ray.hit_info.position;
    if (ray.hit_info.normal * direction <= 0.0) {
      continue;
    }
    t = sqrt(direction * direction);
    if (t <= 0.0) {
      continue;
    }
    direction = direction / t;
    Ray light_ray(ray.hit_info.position, direction);
    bool in_shadow = false;
    // compute shadows
    for (int i = 0; i < num_objects; i++) {
      Shape *shape = (Shape *)scene->objects[i];
      if (shape->Hit(light_ray, t)) {
        in_shadow = true;
        break;
      }
    }
    if (!in_shadow) {
      double lambert = (light_ray.get_direction() * ray.hit_info.normal) * coef;
      colour = colour + light->get_colour() * material->get_colour() * lambert;
      if (dot > 0.0) {
        double specular = pow(dot, 20) * (1.0 - coef);
        colour = colour + light->get_colour() * specular;
      }
    }
  }

  // next reflection
  double reflection = material->get_reflection();
  if (reflection > 0.0 && depth > 0) {
    double t1 = 10000.0;
    RGBColour clr = scene->get_bgcolour();
    RayTrace(reflected_ray, clr, t1, (coef * reflection), depth - 1);
    colour = colour + clr * reflection;
  }

  // next refraction
  if (material->get_transparency() > 0.0 && depth > 0) {
    double refraction_in = material->get_refraction_in();
    double refraction_out = material->get_refraction_out();
    double refraction = refraction_in / refraction_out;
    double prev_dist = ray.get_direction().get_z();
    ray.set_direction(Vector(ray.get_direction().get_x(),
                             ray.get_direction().get_y(),
                             ray.get_direction().get_z() + DISTANCE));

    // total reflection
    Vector direction = ray.get_direction();
    if (refract_(ray.hit_info.normal, direction, refraction_in, refraction_out)) {
      double t1 = 10000.0;
      RGBColour clr = scene->get_bgcolour();
      Ray refracted_ray = Ray(ray.hit_info.position + direction * EPSILON, direction);
      if (RayTrace(refracted_ray, clr, t1, (coef * refraction), depth-1)) {
        RayTrace(refracted_ray, clr, t1, (coef * refraction), depth-1);
        material = refracted_ray.hit_info.material;
      }
      RGBColour transparency = transmission_(material->get_colour(), coef, refracted_ray.hit_info.distance);
      transparency = transparency * material->get_transparency();
      if (clr.get_red() > 1.0 || clr.get_green() > 1.0 || clr.get_blue() > 1.0) {
        clr = scene->get_bgcolour();
      }
      colour = colour + clr * transparency * coef * 0.5;
    }

    // no total reflection
    else {
      double t1 = 10000.0;
      RGBColour clr = scene->get_bgcolour();
      Ray refracted_ray = Ray(ray.hit_info.position + direction * EPSILON, direction);
      if (RayTrace(refracted_ray, clr, t1, (coef * refraction), depth-1)) {
        RayTrace(refracted_ray, clr, t1, (coef * refraction), depth-1);
        material = refracted_ray.hit_info.material;
      }
      double refl = reflectance_(refracted_ray.hit_info.normal, refracted_ray.get_direction(), refraction_in, refraction_out);
      refl = refl * material->get_transparency();
      if (clr.get_red() > 1.0 || clr.get_green() > 1.0 || clr.get_blue() > 1.0) {
        clr = scene->get_bgcolour();
      }
      colour = colour + clr * refl * coef * 0.5;
    }
  }

    return true;
}

// Refraction
bool RayTracer::refract_(Vector const& normal, Vector &direction, double const& n1, double const& n2) const {
  double n = n1 / n2;
  double cos_d = -(normal * direction);
  double sin_t = n * n * (1.0 - cos_d * cos_d);

  if (sin_t > 1.0) {
    return false;
  }

  double cos_t = sqrt(1.0 - sin_t);
  direction = (direction * n) + (normal * (n * cos_d - cos_t));
  return true;
}

bool RayTracer::reflect_(Vector const& normal, Vector &direction) const {
  double cos_d = -(normal * direction);
  direction = direction + normal * cos_d * 2.0;
  return true;
}

double RayTracer::reflectance_(Vector const& normal, Vector const& direction, double const& n1, double const& n2) const {
  double refl = 1.0;
  double r = (n1 - n2) / (n1 + n2);
  r = r * r;
  double cos_d = -(normal * direction);
  if (n1 > n2) {
    double n = n1 / n2;
    double sin_t = n * n * (1.0 - cos_d * cos_d);
    if (sin_t > 1.0) {
      return refl;
    }
    cos_d = sqrt(1.0 - sin_t);
  }
  double x = 1.0 - cos_d;
  refl = r + (1.0 - r) * x * x * x * x * x;

  return refl;
}

// Beer-Lamber-Law
RGBColour RayTracer::transmission_(RGBColour const& clr, double const& coef, double const& dist) const {
  RGBColour absorbance = clr * coef * -dist;
  RGBColour transmission = RGBColour(exp(absorbance.get_red()), exp(absorbance.get_green()), exp(absorbance.get_blue()));
  return transmission;
}
