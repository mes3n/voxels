# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CC = g++
objCFLAGS = -Wextra -g -fmax-errors=10
binCFLAGS = -Wall -g -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLEW

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o
	$(CC) $(binCFLAGS) -o bin/main obj/main.o

# The main.o target can be written more simply

main.o:
	$(CC) $(objCFLAGS) -o obj/main.o -c src/main.cpp
