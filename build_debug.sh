#!/bin/bash
rm -f *.o &&
gcc -c src/*.c src/engine/*.c src/systems/*.c -std=c99 -g -Wall -I include &&
gcc *.o -o bin/debug/linux/game -lSDL2main -lSDL2 -lSDL2_image &&
./bin/debug/linux/game
