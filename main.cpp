#include <math.h>
#include <time.h>
#include <omp.h>
#include "scene/scene.hpp"
#include "world/world.hpp"

int main(int argc, char* argv[]) {
  omp_set_num_threads(THREADS);

  if (argc > 2) {
    World *world = new World();
    fprintf(stdout, "Scene file: %s\n", argv[1]);
    fprintf(stdout, "Images dir: %s\n", argv[2]);
    if (world->Build(argv[1]) == 0) {
      char filename[1024];
      sprintf(filename, "%s/test.tga", argv[2]);
      world->RenderScene(filename);
      fprintf(stdout, "Finished Rendering image\n");
    }
    delete (world);
  } else {
    fprintf(stdout, "Error reading the scene file or images dir\n");
  }

  return 0;
}
