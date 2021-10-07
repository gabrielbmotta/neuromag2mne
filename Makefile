# Makefile for compiling and linking 

CC = g++
FLAGS = -std=c++98 -lpthread -static#-std=c++11 -std=c++14 -std=c++17
FLAGS := -g -O -Wall -Weffc++ -pedantic  \
	-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
	-Wcast-qual -Wconversion \
	-Wdisabled-optimization \
	-Wfloat-equal -Wformat=2 \
	-Wformat-nonliteral -Wformat-security  \
	-Wformat-y2k \
	-Wimport  -Winit-self  -Winline \
	-Winvalid-pch   \
	-Wlong-long \
	-Wmissing-field-initializers -Wmissing-format-attribute   \
	-Wmissing-include-dirs -Wmissing-noreturn \
	-Wpacked -Wpointer-arith \
	-Wredundant-decls \
	-Wshadow -Wstack-protector \
	-Wstrict-aliasing=2 -Wswitch-default \
	-Wswitch-enum \
	-Wunreachable-code -Wunused \
	-Wunused-parameter \
	-Wvariadic-macros \
	-Wwrite-strings \
	# -Wpadded	\
	# -Werror

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
	mkdir -p $(BUILDDIR); mkdir -p $(OUTDIR)

$(OUTDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -I $(SOURCEDIR) $(FLAGS) -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) -c $(FLAGS) $< -I $(SOURCEDIR) -o $@

clean:
	rm -f $(BUILDDIR)/*o $(OUTDIR)/$(EXECUTABLE)


