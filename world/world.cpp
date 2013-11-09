#include <time.h>
#include "world/world.hpp"
#include <omp.h>
#include <vector>

World::World(void) {}

World::~World(void) {
  if (scene) {
    delete scene;
  }
}

int World::Build(char* filename) {
  scene = new Scene(filename);

  if (scene->Read() < 1) {
    fprintf(stdout, "\nWorld::Build: Error Reading File %s\n", filename);
    return -1;
  } else {
#ifdef DEBUG
    Sphere *sphere = scene->get_spheres();
    Plane *plane = scene->get_planes();
    Light *light = scene->get_lights();
    scene->Print();
    fprintf (stdout, "\nSpheres:\n"); 
    for (int i = 0; i < scene->get_number_of_spheres(); sphere++,i++) { 
      fprintf (stdout, " Sphere[%d]:\n", i); 
      Vector v = sphere->get_center(); 
      fprintf (stdout, "   Center:        %7.2f, %7.2f, %7.2f\n", v.get_x(), v.get_y(), v.get_z()); 
      fprintf (stdout, "   Radius:        %7.2f\n", sphere->get_radius()); 
      fprintf (stdout, "   StartAngle:    %7.2f\n", sphere->get_start_angle());
      Material *m = sphere->get_material();
      fprintf (stdout, "   Material:\n");
      fprintf (stdout, "      Reflection:    %7.2f\n", m->get_reflection());
      fprintf (stdout, "      RefractionIn:  %7.2f\n", m->get_refraction_in());
      fprintf (stdout, "      RefractionOut: %7.2f\n", m->get_refraction_out());
      fprintf (stdout, "      Transparency: %7.2f\n", m->get_transparency());
      RGBColour c = m->get_colour();
      fprintf (stdout, "      Colour:         %7.2f, %7.2f, %7.2f\n", c.get_red(), c.get_green(), c.get_blue());
    }
    fprintf (stdout, "\nPlanes:\n"); 
    for (int i = 0; i < scene->get_number_of_planes(); plane++,i++) { 
      fprintf (stdout, " Plane[%d]:\n", i); 
      Vector v = plane->get_point(); 
      fprintf (stdout, "   Point:         %7.2f, %7.2f, %7.2f\n", v.get_x(), v.get_y(), v.get_z());
      v = plane->get_normal_vector(); 
      fprintf (stdout, "   Normal Vector: %7.2f, %7.2f, %7.2f\n", v.get_x(), v.get_y(), v.get_z()); 
      Material *m = plane->get_material();
      fprintf (stdout, "   Material:\n");
      fprintf (stdout, "      Reflection:    %7.2f\n", m->get_reflection());
      fprintf (stdout, "      RefractionIn:  %7.2f\n", m->get_refraction_in());
      fprintf (stdout, "      RefractionOut: %7.2f\n", m->get_refraction_out());
      fprintf (stdout, "      Transparency: %7.2f\n", m->get_transparency());
      RGBColour c = m->get_colour();
      fprintf (stdout, "      Colour:         %7.2f, %7.2f, %7.2f\n", c.get_red(), c.get_green(), c.get_blue());
    }
    fprintf (stdout, "\nLights:\n"); 
    for (int i = 0; i < scene->get_number_of_lights(); light++,i++) { 
      fprintf (stdout, " Light[%d]:\n", i); 
      Vector v = light->get_position(); 
      fprintf (stdout, "   Position:         %7.2f, %7.2f, %7.2f\n", v.get_x(), v.get_y(), v.get_z());
      RGBColour c = light->get_colour();
      fprintf (stdout, "      Colour:         %7.2f, %7.2f, %7.2f\n", c.get_red(), c.get_green(), c.get_blue());
    }
#endif
    return 0;
  }

  return -1;
}

bool World::RenderScene(char* filename) {
  RayTracer *ray_tracer;
  ray_tracer = new RayTracer(scene);
  double const distance = DISTANCE;
  int const width = scene->get_width();
  int const height = scene->get_height();

  Ray ray;

  std::vector<RGBColour> buffer (width*height);

  int VIEWING_TYPE = scene->get_view_type();
  double ZOOM = 1.0 / scene->get_zoom();
  double INV_GAMMA = 1.0 / scene->get_gamma();
  for (int y = 0; y < height; y++) {
#pragma omp parallel for private (ray) shared(ray_tracer, buffer)
    for (int x = 0; x < width; x++) {
      const double coef = 1.0;
      const int depth = 10;
      double t = DEFAULT_T;
      RGBColour colour = scene->get_bgcolour();
      if (VIEWING_TYPE == ORTHOGRAPHIC) {
        ray.set_origin(Vector(ZOOM * x, ZOOM * y, -distance));
        ray.set_direction(Vector(0.0, 0.0, distance));
      } else if (VIEWING_TYPE == PERSPECTIVE) {
        ray.set_origin(Vector(width / 2.0, height / 2.0, -distance));
        ray.set_direction(Vector(ZOOM * (x - width / 2.0 + 0.5), ZOOM * (y - height / 2.0 + 0.5), distance));
      }
      Vector normalized_direction(ray.get_direction());
      normalized_direction.Normalize();
      ray.set_direction(normalized_direction);
      ray_tracer->RayTrace(ray, colour, t, coef, depth);

      // Gamma correction
      // Colour = Colour ^ (1 / gamma)

      colour = colour.power(INV_GAMMA);
      colour = colour * 255.0;
      colour.set_red(min(colour.get_red(), 255.0));
      colour.set_green(min(colour.get_green(), 255.0));
      colour.set_blue(min(colour.get_blue(), 255.0));

      buffer[y * width + x] = colour;
    }
  }

  // 24 bit RGB uncompressed TGA image
  TGA * tga = new TGA (24, 2, scene->get_width(), scene->get_height());

  // Fill TGA buffer
  for (RGBColour colour : buffer) {
    tga->set_colour(colour.get_red(), colour.get_green(), colour.get_blue());
  }
  // Write TGA image buffer to file
  tga->Write(filename);
  delete(tga);
  return true;
}

double World::min(double const& d1, double const& d2) {
  return (d1 > d2) ? d2 : d1;
}
