#include<stdint.h>
#include<stdio.h>
#include<string>

using namespace std;

struct bmpSignature
{
    unsigned char s[2];
};

struct headerFormat
{
    bmpSignature signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelOffset;
};

struct dibFormat
{
    uint32_t dibSize;
    uint32_t imageWidth;
    uint32_t imageHeight;
    uint16_t colorPlanes;
    uint16_t  colorDepth;
    uint32_t compression;
    uint32_t pixelArrSize;
    uint32_t horizontalPixel;
    uint32_t verticalPixel;
    uint32_t numColor;
    uint32_t numImportantColor;
};

struct Color
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct colorTable 
{
    Color *colors;
    uint32_t length;
};

struct pixelArray
{
    Color **pixels;
    uint32_t rowColor;
    uint32_t columnColor;
};

bool isBMP(string fi);
void readHeaderFormat(string fi, headerFormat &header);
void readDIB(string fi, dibFormat &dib);
void readBmpPixelArray(string fi, headerFormat header, dibFormat dib, pixelArray &data);

