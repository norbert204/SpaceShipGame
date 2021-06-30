#!/bin/bash
rm -f *.o &&
gcc -c src/*.c -std=c99 -g -Wall -I include &&
gcc *.o -o bin/debug/game -lSDL2main -lSDL2 -lSDL2_image &&
./bin/debug/game
