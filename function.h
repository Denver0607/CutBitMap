#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct BmpDib
{
    uint32_t dibSize;
    int32_t imageWidth;
    int32_t imageHeight;
    uint16_t colorPlanCOunt;
    uint16_t pixelSize;
    uint32_t compressMethod;
    uint32_t bitmapByteCount;
    int32_t horizontalResolution;
    int32_t verticalResolution;
    uint32_t colorCount;
    uint32_t importantColorCount;
};


struct Color
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct ColorTable
{
    Color* colors;
    uint32_t length;
};

struct PixelArray
{
    char *rawData;
    int rawDataSize;
    char padding;
    int lineSize;
    Color **pixels;
};


