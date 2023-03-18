#include"readBmpFormat.h"

void printBmpHeader(headerFormat header);
void printBmpDib(dibFormat dib);
void printPixelArray(pixelArray data, char padding);
void printBMPtoTerminal(BMP b, bool check);
void deletePixelArray(pixelArray data);