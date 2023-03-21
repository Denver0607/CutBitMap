#pragma once
#pragma pack(1)

#include<stdint.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<stdlib.h>

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
    uint16_t colorDepth; //which is the number of bits per pixel (pixel size). Typical values are 1, 4, 8, 16, 24 and 32
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
    Color* colors;
    uint32_t length;
};

struct pixelArray
{
    Color** pixels;
    uint32_t rowColor;
    uint32_t columnColor;
};

struct BMP
{
    headerFormat header;
    dibFormat dib;
    pixelArray pA;
    colorTable cT;
};

// READING BMP FILE FORMAT
bool isBMP(FILE* f);
void readHeaderFormat(FILE* f, headerFormat& header);
void printBmpHeader(headerFormat header);
void readDIB(FILE* f, dibFormat& dib);
void printBmpDib(dibFormat dib);
void readPixelLine(FILE* f, Color*& line, uint32_t length);
void scanPadding(FILE* f, char count);
void readPixelArray(FILE* f, headerFormat header, dibFormat dib, pixelArray& data);
bool readBMPfile(char* filename, BMP& b);

// PRINT BMP FILE
void printBMPfile(char* fileName, BMP b);
void deleteBMPpixelArray(pixelArray data);

// CUT BMP
void copyHeader(BMP sourceFile, BMP &destinationFile, uint32_t height, uint32_t width);
void copyDIB(BMP sourceFile, BMP &destinationFile,uint32_t height, uint32_t width);
BMP calculatePartOfBmpFile(BMP bmp, uint32_t row, uint32_t column, uint32_t sizeRow, uint32_t sizeColumn);

// SPLIT BMP FILE
void makeFile(char* name, const char* extension, char* filename, int i, int j);
void makeDestName(char* s, char* cut);
void cutBMPfile(char* sourceFile, char* destName, int heightSplit, int widthSplit);
