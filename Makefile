CC=g++
CFLAGS= -c -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11 
LDFLAGS=
LIBS=  -lGL -lGLU -lglut -lfmodex64 
SOURCES=main.cpp src/GLDraw.cpp src/FMODEq.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hello

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o  $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o  $@



