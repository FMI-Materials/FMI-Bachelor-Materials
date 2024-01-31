GCC=g++
FLAGS=-std=c++0x

ALGORITHM_CPP:=$(wildcard algorithm/*.cpp)
MAIN_CPP:=main.cpp

OUTPUT:=main.o

LIB_HFILES:= -IAlgorithm -pthread

all: algorithm_release
debug: algorithm_debug

algorithm_release:
	$(GCC) -g $(MAIN_CPP) $(ALGORITHM_CPP) -o $(OUTPUT) $(LIB_HFILES) $(FLAGS)

algorithm_debug:
	$(GCC) -g $(MAIN_CPP) $(ALGORITHM_CPP) -o $(OUTPUT) $(LIB_HFILES) $(FLAGS) -DDEBUG

clean:
	rm main.o
	rm -r main.o.*
