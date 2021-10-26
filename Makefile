# Makefile for compiling and linking 

SOURCEDIR = src
EXECUTABLE = neuromag2mne
OUTDIR-RELEASE = out-release
BUILDDIR-RELEASE = build-release
OUTDIR-DEBUG = out-debug
BUILDDIR-DEBUG = build-debug

DIRECTORIES = $(wildcard $(SOURCEDIR)/*)
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
SOURCES += $(wildcard $(SOURCEDIR)/*/*.cpp)

CXXFLAGSDEBUG := -g \
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

CXXFLAGS-COMMON=$(CXXFLAGSDEBUG) -Werror -std=c++98 #-std=c++11 -std=c++14 -std=c++17

CXXFLAGS-RELEASE=-DNDEBUG -O3 $(CXXFLAGS-COMMON)
CXXFLAGS-DEBUG=-DDEBUG -g $(CXXFLAGS-COMMON)  $(CXXFLAGSDEBUG)

##############################################################################
##############################################################################

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
	CXX = clang++
else ifeq ($(UNAME),Linux)
	CXX = g++
	CXXFLAGS += -pthread
else
# todo we still need to do this.
endif

OBJECTS-RELEASE = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR-RELEASE)/%.o,$(SOURCES))
OBJECTS-DEBUG = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR-DEBUG)/%.o,$(SOURCES))

##############################################################################
##############################################################################

all: release debug

release: $(OUTDIR-RELEASE)/$(EXECUTABLE)

debug: $(OUTDIR-DEBUG)/$(EXECUTABLE)

$(OUTDIR-RELEASE)/$(EXECUTABLE): $(OBJECTS-RELEASE)
	mkdir -p $(@D)
	$(CXX) $^ $(CXXFLAGS) -o $@

$(OBJECTS-RELEASE): $(BUILDDIR-RELEASE)/%.o : $(SOURCEDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OUTDIR-DEBUG)/$(EXECUTABLE): $(OBJECTS-DEBUG)
	mkdir -p $(@D)
	$(CXX) $^ $(CXXFLAGS) -o $@

$(OBJECTS-DEBUG): $(BUILDDIR-DEBUG)/%.o : $(SOURCEDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -fr build*
	rm -fR out*
