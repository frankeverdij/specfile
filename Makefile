# specfile/readspec Makefile

# gcc compiler
CC = gcc

# g++ compiler
CXX = g++

# gcc compiler flags
CFLAGS = -g -Wall -I.

# g++ compiler flags
CXXFLAGS = -g -Wall -I.

# g++ linker
CXX_LD = $(CXX)

#gcc linker
LD = $(CC)

# linker flags
LDFLAGS = 

# name of executable
RS_EXE = readspec
SF_EXE = specfile

# list of all sources
RS_SOURCES = $(wildcard *.cpp)
SF_SOURCES = specfile.c

# list of all objects
RS_OBJECTS = $(RS_SOURCES:.cpp=.o)
SF_OBJECTS = $(SF_SOURCES:.c=.o)

# Makefile
all: rs sf
rs: $(RS_OBJECTS)
	$(CXX_LD) -o $(RS_EXE) $(RS_OBJECTS) $(LDFLAGS)
sf: $(SF_OBJECTS)
	$(LD) -o $(SF_EXE) $(SF_OBJECTS) $(LDFLAGS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning everything
clean:
	rm -f $(RS_EXE) $(RS_OBJECTS) $(SF_EXE) $(SF_OBJECTS)
# End
