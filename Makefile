CC := g++
CFLAGS := -Wall -Wextra -Wcast-align -Wfloat-equal -Wpointer-arith -Wundef -O2 -fstack-protector
LIBS :=

EXENAME := graph

SOURCEDIR := src

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

.PHONY: all clean

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXENAME) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCEDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	-@rm $(OBJECTS)
