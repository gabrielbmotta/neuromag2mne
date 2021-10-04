# Makefile for compiling and linking 

CC = g++
FLAGS = -g -c -std=c++98#-std=c++11 -std=c++14 -std=c++17

SOURCEDIR = src
OUTDIR = out
BUILDDIR = build
EXECUTABLE = neuromag2mne
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# SOURCES := $(filter-out $(SOURCEDIR)/datawatcher.cpp, $(SOURCES))
# SOURCES := $(filter-out $(SOURCEDIR)/commandwatcher.cpp, $(SOURCES))

##############################################################################
all: dir $(OUTDIR)/$(EXECUTABLE)

dir: 
	mkdir -p $(BUILDDIR)

$(OUTDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -I $(SOURCEDIR) -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) -c $(FLAGS) $< -I $(SOURCEDIR) -o $@

clean:
	rm -f $(BUILDDIR)/*o $(OUTDIR)/$(EXECUTABLE)

