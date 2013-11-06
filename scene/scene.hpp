#ifndef SCENE_HPP
#define SCENE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "def.hpp"
#include "colour/rgb_colour.hpp"
#include "light/light.hpp"
#include "material/material.hpp"
//#include "path/path.hpp"
#include "shape/shape.hpp"
#include "shape/plane.hpp"
#include "shape/sphere.hpp"
#include "scene/parse.hpp"

class Scene {
  private:
    int version_;
    int width_;
    int height_;
    int view_type_;
    double zoom_;
    double gamma_;
    RGBColour bgcolour_;
    int number_of_materials_;
//    int number_of_paths_;
    int number_of_spheres_;
    int number_of_planes_;
    int number_of_lights_;

    Sphere *sphere_;
    Plane *plane_;
    Material *material_;
//    Path *path_;
    Light *light_;
    Parse *parse_;

    int count_, error_number_;
    FILE *file_;
    char *filename_;
    int shape_read_;
    int scene_read_, sphere_read_, plane_read_, light_read_, material_read_; // path_read_;

    char* ReadScene_(char *buffer);
    char* ReadSphere_(char *buffer);
    char* ReadPlane_(char *buffer);
    char* ReadLight_(char *buffer);
    char* ReadMaterial_(char *buffer);
    char* ReadPath_(char *buffer);

  public:
    int **objects;

    Scene(char* filename);
    ~Scene(void);

    int Read(void);
    int get_version(void) const;
    int get_width(void) const;
    int get_height(void) const;
    int get_view_type(void) const;
    double get_zoom(void) const;
    void set_zoom(double const& zoom);
    double get_gamma(void) const;
    RGBColour get_bgcolour(void) const;

    int get_number_of_shapes(void) const;
    int get_number_of_spheres(void) const;
//    int get_number_of_paths(void) const;
    int get_number_of_planes(void) const;
    int get_number_of_lights(void) const;

    Sphere* get_spheres(void);
//  Path* get_paths(void);
    Plane* get_planes(void);
    Light* get_lights(void);

    void Print(void) const;
};

#endif
