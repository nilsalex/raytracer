CXX = g++
OPT = -O2 -march=corei7
CFLAGS = $(OPT) -Wall -Wextra -pedantic -std=gnu++0x
LDFLAGS =
INCLUDE = -I.

_OBJECTS = main.o vector.o ray.o rgb_colour.o material.o
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

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)main
