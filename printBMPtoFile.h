#pragma once
#include "readBmpFormat.h"

void printHeaderBMP(FILE * f, headerFormat  header);
void printDIB(FILE * f, dibFormat dib);
void printPixelArray(FILE *f, pixelArray data, char padding);
void printBMPfile(char * fileName, BMP b);
void deleteBMPpixelArray(pixelArray data);
