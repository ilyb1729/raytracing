CXX = g++
CXXFLAGS = -std=c++20 -Wall -MMD -Werror=vla
SRCS = $(shell find . -type f -name "*.cc")
OBJECTS = ${SRCS:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = raytracer

.PHONY: all clean

all: ${EXEC}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

-include ${DEPENDS}

clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}