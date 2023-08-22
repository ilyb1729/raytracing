CXX = g++
CXXFLAGS = -std=c++20 -Wall -MMD -Werror=vla -pthread
SRCS = $(shell find . -type f -name "*.cc")
OBJECTS = ${SRCS:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = raytracer

.PHONY: all clean img cleantmp cleanfuck

all: ${EXEC}

img: ${EXEC}
	./raytracer
	display ./img.ppm

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

-include ${DEPENDS}

cleantmp:
	rm -f ./tmp*-*
	rm -f ./img.ppm

cleanfuck:
	rm -f ./tmp1-*
	rm -f ./tmp2-*
	rm -f ./tmp3-*
	rm -f ./tmp4-*
	rm -f ./img.ppm

clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
	rm -f ./img.ppm