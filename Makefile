# Makefile for compiling and linking 

SOURCEDIR = src
EXECUTABLE = neuromag2mne

OUTDIR-RELEASE = out-release
BUILDDIR-RELEASE = build-release
OUTDIR-DEBUG = out-debug
BUILDDIR-DEBUG = build-debug

BUILDDIR-TEST-RELEASE = build-test-release
OUTDIR-TEST-RELEASE = out-test-release

BUILDDIR-TEST-DEBUG = build-test-debug
OUTDIR-TEST-DEBUG = out-test-debug

TEST-DIR = test
TEST-EXECUTABLE = run_tests

DIRECTORIES = $(wildcard $(SOURCEDIR)/*)
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
SOURCES += $(wildcard $(SOURCEDIR)/*/*.cpp)

TEST-SOURCES = $(wildcard $(TEST-DIR)/*.cpp)

##############################################################################

CXXFLAGS-WARNINGS := -Wall  -Wpedantic \
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

CXXFLAGS-COMMON=$(CXXFLAGS-WARNINGS) -Werror -std=c++98 #-std=c++11 -std=c++14 -std=c++17

CXXFLAGS-RELEASE=-DNDEBUG -O3 $(CXXFLAGS-COMMON)
CXXFLAGS-DEBUG=-DDEBUG -g $(CXXFLAGS-COMMON)

CXXFLAGS-TEST-RELEASE=-DNDEBUG -O3 -std=c++98
CXXFLAGS-TEST-DEBUG=-DDEBUG -g -std=c++98

##############################################################################
##############################################################################
#CXXFLAG-COVERAGE=--coverage
CXXFLAGS-COVERAGE=-fprofile-instr-generate -fcoverage-mapping
CXXFLAGS-COVERAGE=-fprofile-arcs -ftest-coverage

##############################################################################
##############################################################################

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
	CXX = clang++
else ifeq ($(UNAME),Linux)
	CXX = g++
	CXXFLAGS-RELEASE += -pthread
	CXXFLAGS-DEBUG += -pthread
else
# todo we still need to do this.
endif

OBJECTS-RELEASE = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR-RELEASE)/%.o,$(SOURCES))
OBJECTS-DEBUG = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR-DEBUG)/%.o,$(SOURCES))

OBJECTS-NO-MAIN = $(filter-out %/main.o,$(OBJECTS-RELEASE))
OBJECTS-TEST-RELEASE = $(patsubst $(TEST-DIR)/%.cpp,$(BUILDDIR-TEST-RELEASE)/%.o,$(TEST-SOURCES))
OBJECTS-TEST-DEBUG = $(patsubst $(TEST-DIR)/%.cpp,$(BUILDDIR-TEST-DEBUG)/%.o,$(TEST-SOURCES))

##############################################################################
##############################################################################

all: release debug test

release: $(OUTDIR-RELEASE)/$(EXECUTABLE)

debug: $(OUTDIR-DEBUG)/$(EXECUTABLE)

test: test-release

test-release: $(OUTDIR-TEST-RELEASE)/$(TEST-EXECUTABLE)

test-debug: $(OUTDIR-TEST-DEBUG)/$(TEST-EXECUTABLE)

$(OUTDIR-RELEASE)/$(EXECUTABLE): $(OBJECTS-RELEASE)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS-RELEASE) $(CXXFLAGS-COVERAGE) $^ -o $@

$(OBJECTS-RELEASE): $(BUILDDIR-RELEASE)/%.o : $(SOURCEDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS-RELEASE) $(CXXFLAGS-COVERAGE) -c $< -o $@

$(OUTDIR-DEBUG)/$(EXECUTABLE): $(OBJECTS-DEBUG)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS-DEBUG) $^ -o $@

$(OBJECTS-DEBUG): $(BUILDDIR-DEBUG)/%.o : $(SOURCEDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS-DEBUG) -c $< -o $@

$(OUTDIR-TEST-RELEASE)/$(TEST-EXECUTABLE) : $(OBJECTS-TEST-RELEASE)
	mkdir -p $(@D)
	$(CXX) $(OBJECTS-NO-MAIN) $(CXXFLAGS-TEST-RELEASE) $(CXXFLAGS-COVERAGE) $^ -o $@

$(OBJECTS-TEST-RELEASE): $(BUILDDIR-TEST-RELEASE)/%.o : $(TEST-DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS-TEST-RELEASE) $(CXXFLAGS-COVERAGE) -c $< -o $@

$(OUTDIR-TEST-DEBUG)/$(TEST-EXECUTABLE) : $(OBJECTS-TEST-DEBUG)
	mkdir -p $(@D)
	$(CXX) $(OBJECTS-NO-MAIN) $(CXXFLAGS-TEST-DEBUG) $^ -o $@

$(OBJECTS-TEST-DEBUG): $(BUILDDIR-TEST-DEBUG)/%.o : $(TEST-DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS-TEST-DEBUG) -c $< -o $@

clean:
	rm -fr build*
	rm -fR out*
