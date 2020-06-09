COMPILER = g++
COMPLIE = -c
VERSION = -std=c++11
CC = ${COMPILER} ${COMPLIE} ${VERSION}

SOURCES := ${shell find * -type f -name "*.cpp"}
OBJDIR  := Build
OBJECTS := ${addprefix ${OBJDIR}/,${SOURCES:.cpp=.o}}

all: utrip.out

utrip.out: ${OBJECTS}
	${COMPILER} ${VERSION} $^ -o $@

${OBJECTS}: ${OBJDIR}/%.o: %.cpp
	mkdir -p ${@D}
	${CC} $< -o $@

-include $(OBJECTS:.o=.d)

clean:
	rm utrip.out
	rm -rfv Build