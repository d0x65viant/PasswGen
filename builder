#!/bin/bash
windres my.rc -O coff -o my.res
gcc `pkg-config --cflags gtk+-3.0` -o main -lgdi32 -Wl,-subsystem,windows *.c my.res `pkg-config --libs gtk+-3.0`