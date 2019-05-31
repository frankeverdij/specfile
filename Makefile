# specfile/readspec Makefile

# g++ compiler
CXX = g++

# g++ compiler flags
CXXFLAGS = -O2 -I.

# linker
LD = $(CXX)

# linker flags
LDFLAGS = 

# name of executable
EXE = readspec

# list of all sources
SOURCES = $(wildcard *.cpp)

# list of all objects
OBJECTS = $(SOURCES:.cpp=.o)

# Makefile
all: $(OBJECTS)
	$(LD) -o $(EXE) $(OBJECTS) $(LDFLAGS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning everything
clean:
	rm -f $(EXE) $(OBJECTS)
# End
