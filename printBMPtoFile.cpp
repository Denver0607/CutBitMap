#include "printBMPtoFile.h"
#include <stdio.h>
#include <stdlib.h>

void printHeaderBMP(FILE * f, headerFormat  header)
{
	if (f == NULL) return;
	fseek(f, 0, SEEK_SET);
	fwrite(&header, sizeof(headerFormat), 1, f);
}

void printDIB(FILE * f, dibFormat dib)
{
	if (f == NULL) return;
	fseek(f, sizeof(headerFormat), SEEK_SET);
	fwrite(&dib, sizeof(dibFormat), 1, f);
}

void printPixelArray(FILE *f, pixelArray data, char padding)
 {
	char * p = "\0\0\0";
	for (int i = data.rowColor - 1; i >= 0; i--) {
		fwrite(data.pixels[i], sizeof(Color), data.columnColor, f);
		fwrite(p, sizeof(char), padding, f);
	}
}


void printBMPfile(char * fileName, BMP b)
{
	FILE *f = fopen(fileName, "wb");
	if (f == NULL) return;
	printHeaderBMP(f, b.header);
	printDIB(f, b.dib);
	char paddingCount = (4 - (b.dib.imageWidth * (b.dib.colorDepth/ 8) % 4)) % 4;
	printPixelArray(f, b.pA, paddingCount);
	fclose(f);
}

void deleteBMPpixelArray(pixelArray data)
{
	for (int i = 0; i < data.rowColor; i++)
		free(data.pixels[i]);
	free(data.pixels);
}
