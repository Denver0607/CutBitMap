#include"readBmpFormat.h"
#include"printBmpFormat.h"
#include"printBMPtoFile.h"
#include "splitBMP.h"

// int getNumberOfDigit(int n);
// void convertToCharPointer(int n, char*& result);
// void getDestinationFile(char* bmpPath, char*& destinationFile, int fileNumber);
// void splitBMPfile(char* sourceFile, int heightSplit, int widthSplit);

void makeFile(char* name, const char* extendsion, char* filename, int i, int j);
void splitBMPfile(char* sourceFile, char* destName, int hsplit, int wsplit);
void makeDestName(char* s, char* cut);
