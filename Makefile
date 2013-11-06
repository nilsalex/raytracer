CXX = g++
OPT = -ggdb -march=corei7
CFLAGS = $(OPT) -Wall -Wextra -pedantic -std=gnu++0x
LDFLAGS =
INCLUDE = -I. 

_OBJECTS = main.o world.o ray_tracer.o scene.o sphere.o plane.o shape.o light.o vector.o ray.o rgb_colour.o material.o tga.o parse.o
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJECTS))

OUT = .
ODIR = bin/obj
SDIR = .

all: main

main: $(_OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(OUT)/$@

main.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/main.cpp

world.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/world/world.cpp

ray_tracer.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/trace/ray_tracer.cpp

scene.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/scene/scene.cpp

sphere.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/shape/sphere.cpp

plane.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/shape/plane.cpp

shape.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/shape/shape.cpp

light.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/light/light.cpp

vector.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/math/vector.cpp

ray.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/math/ray.cpp

rgb_colour.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/colour/rgb_colour.cpp

material.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/material/material.cpp

tga.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/image/tga.cpp

parse.o:
	mkdir -p $(ODIR)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $(ODIR)/$@ $(SDIR)/scene/parse.cpp

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)main
