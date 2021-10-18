# Makefile for compiling and linking 

SOURCEDIR = src
OUTDIR = out
BUILDDIR = build
EXECUTABLE = neuromag2mne
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

UNAME := $(shell uname)

CXXFLAGS += -std=c++98 -pthread #-std=c++11 -std=c++14 -std=c++17
CXXFLAGSDEBUG := -g -O \
	-Wall  \
	-Weffc++ -Wcast-qual -Wconversion -Wmissing-field-initializers -Wmissing-format-attribute \
	-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
	-Wdisabled-optimization \
	-Wfloat-equal -Wformat=2 \
	-Wformat-nonliteral -Wformat-security  \
	-Wformat-y2k \
	-Wimport  -Winit-self  -Winline \
	-Winvalid-pch   \
	-Wlong-long \
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

ifeq ( $(UNAME), Dawrin)
	CXX = clang++
	CXXFLAGS +=
else ifeq ( $(UNAME), Linux)
	CXX = g++
	CXXFLAGS +=
else
# we still need to do this.
endif

##############################################################################

all: dir_prepare executable

debug: CXXFLAGS += -DDEBUG $(CXXFLAGSDEBUG)
debug: executable

executable: $(OUTDIR)/$(EXECUTABLE)

dir_prepare:
	mkdir -p $(BUILDDIR); mkdir -p $(OUTDIR)

$(OUTDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -I $(SOURCEDIR) -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -I $(SOURCEDIR) -o $@

clean:
	rm -f $(BUILDDIR)/*o $(OUTDIR)/$(EXECUTABLE)

