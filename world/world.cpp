#include <time.h>
#include "world/world.hpp"

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
                Sphere *sphere = scene->get_spheres();
                scene->Print();
                fprintf (stdout, "\nSpheres:\n"); 
                for (int i = 0; i < scene->get_number_of_spheres(); sphere++,i++) 
                { 
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
                        fprintf (stdout, "      Color:         %7.2f, %7.2f, %7.2f\n", c.get_red(), c.get_green(), c.get_blue());
                }


    return 0;
  }

  return -1;
}

bool World::RenderScene(char* filename) {
  RayTracer *ray_tracer;
  ray_tracer = new RayTracer(scene);
  // 24 bit RGB uncompressed TGA image
  TGA *tga = new TGA (24, 2, scene->get_width(), scene->get_height());
  double distance = DISTANCE;
  Ray ray;

  int VIEWING_TYPE = scene->get_view_type();
  double ZOOM = 1.0 / scene->get_zoom();
  double INV_GAMMA = 1.0 / scene->get_gamma();
  for (int y = 0; y < scene->get_height(); y++) {
    for (int x = 0; x < scene->get_width(); x++) {
      const double coef = 1.0;
      const int depth = 3;
      double t = 10000.0;
      RGBColour colour = scene->get_bgcolour();
      if (VIEWING_TYPE == ORTHOGRAPHIC) {
        ray.set_origin(Vector(ZOOM * x, ZOOM * y, -distance));
        ray.set_direction(Vector(0.0, 0.0, distance));
      } else if (VIEWING_TYPE == PERSPECTIVE) {
        ray.set_origin(Vector(scene->get_width() / 2.0, scene->get_height() / 2.0, -distance));
        ray.set_direction(Vector(ZOOM * (x - scene->get_width() / 2.0 + 0.5), ZOOM * (y - scene->get_height() / 2.0 + 0.5), distance));
      }
      Vector normalized_direction(ray.get_direction());
      normalized_direction.Normalize();
      ray.set_direction(normalized_direction);
      ray_tracer->RayTrace(ray, colour, t, coef, depth);

      // Gamma correction
      // Colour = Colour ^ (1 / gamma)

      colour = colour.power(INV_GAMMA);
      colour = colour * 255.0;
      colour.set_red(min(colour.get_red(), 0));
      colour.set_green(min(colour.get_green(), 0));
      colour.set_blue(min(colour.get_blue(), 0));

      // Fill TGA image buffer

      tga->set_colour((int)colour.get_red(), (int)colour.get_green(), (int)colour.get_blue());
    }
  }

  // Write TGA image buffer to file
  tga->Write(filename);
  delete(tga);
  return true;
}

double World::min(double const& d1, double const& d2) {
  return (d1 > d2) ? d2 : d1;
}
