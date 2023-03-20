#include"readBmpFormat.h"
#include<Windows.h>

void printBmpHeader(headerFormat header);
void printBmpDib(dibFormat dib);
void printPixelArray(pixelArray data, char padding);
void printBMPtoTerminal(BMP b);
void drawBMP(dibFormat dib, pixelArray data);
void deletePixelArray(pixelArray data);

