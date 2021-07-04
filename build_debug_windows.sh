#!/bin/bash
rm -f *.o &&
x86_64-w64-mingw32-gcc -c src/*.c -std=c99 -g -Wall -I include -ISDL_windows/include -LSDL_windows/lib &&
x86_64-w64-mingw32-gcc *.o -o bin/debug/windows/game.exe -ISDL_windows/include -LSDL_windows/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image