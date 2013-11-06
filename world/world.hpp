#ifndef WORLD_H
#define WORLD_H

#include "image/tga.hpp"
#include "scene/scene.hpp"
#include "trace/ray_tracer.hpp"

class World {
  private:
    Scene* scene;
    double min(double const& d1, double const& d2);

  public:
    World(void);
    ~World(void);

    int Build(char* filename);
    bool RenderScene(char* filename);
//    bool RenderAnimation(char* dir);
};

#endif
