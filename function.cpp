#include"function.h"

const char* BMP_EXT = ".bmp";

void makeFile(char* name, const char* extendsion, char* filename, int i, int j)
{
    char tmp[4] = { i + 49, 'x', j + 49, '\0' };
    strcpy(filename, name);
    strcat(filename, tmp);
    strcat(filename, extendsion);
}

void splitBMPfile(char* sourceFile, char* destName, int hsplit, int wsplit)
{
    BMP bmp_src, bmp_dest;
    if (!readBMPfile(sourceFile, bmp_src)) return;
    int pWidth = bmp_src.dib.imageWidth / wsplit;
    int pHeight = bmp_src.dib.imageHeight / hsplit;
    int x, y;
    char* destFile = (char*)malloc((strlen(destName + strlen(BMP_EXT)) + 3) * sizeof(char));

    x = 0;
    for (int i = 0; i < hsplit; i++) {
        y = 0;
        for (int j = 0; j < wsplit; j++) {
            bmp_dest = cutBmpFile(bmp_src, x, y, pHeight, pWidth);
            makeFile(destName, BMP_EXT, destFile, i, j);
            printBMPfile(destFile, bmp_dest);
            deleteBMPpixelArray(bmp_dest.pA);
            y += pWidth;
        }
        x += pHeight;
    }
    deleteBMPpixelArray(bmp_src.pA);
}

void makeDestName(char* s, char* cut)
{
    int start = strlen(s), i = 0;
    while (s[start] != '/' && start >= 0) start--;
    start++;
    while (s[start] != '.' && start < strlen(s)) {
        cut[i++] = s[start++];
        //i++;
    }
    cut[i] = '\0';
}

// int getNumberOfDigit(int n)
// {
//     int count = 0;
//     while (n > 0)
//     {
//         n /= 10;
//         count++;
//     }
//     return count;
// }

// void convertToCharPointer(int n, char*& result)
// {
//     result = NULL;
//     if (n < 10)
//     {
//         result = new char[3];
//         result[0] = '0';
//         result[1] = n + '0';
//         result[3] = '\0';
//         return;
//     }
//     int num = getNumberOfDigit(n);
//     result = new char[num + 1];
//     result[num] = '\0';
//     while (n > 0)
//     {
//         result[num - 1] = (n % 10) + '0';
//         n /= 10;
//         num--;
//     }
//     return;
// }


// void getDestinationFile(char* bmpPath, char*& destinationFile, int fileNumber)
// {
//     char* fileNumberInChar = NULL;
//     convertToCharPointer(fileNumber, fileNumberInChar);
//     destinationFile = new char[strlen(bmpPath) + 8];
//     string temp=bmpPath;
//     temp=(char *)temp.substr(0,temp.size()-4);
//     destinationFile[0] = '\0';
//     strcat(destinationFile, bmpPath);
//     strcat(destinationFile, ".part");
//     strcat(destinationFile, fileNumberInChar);
//     delete[] fileNumberInChar;
// }

// void splitBMPfile(char* sourceFile, int heightSplit, int widthSplit)
// {
//     BMP bmpSource, bmpDestination;
//     char *destFile;
//     if (!readBMPfile(sourceFile, bmpSource))
//         return;
//     int pWidth = bmpSource.dib.imageWidth / widthSplit;
//     int pHeight = bmpSource.dib.imageHeight / heightSplit;
//     int x, y,count;
//     x = count=0;
//     for (int i = 0; i < heightSplit; i++) 
//     {
//         y = 0;
//         for (int j = 0; j < widthSplit; j++) 
//         {
//             count++;
//             bmpDestination = cutBmpFile(bmpSource, x, y, pHeight, pWidth);
//             getDestinationFile(sourceFile,destFile,count);
//             printBMPfile(destFile, bmpDestination);
//             deleteBMPpixelArray(bmpDestination.pA);
//             y += pWidth;
//         }
//         x += pHeight;
//     }
//     deleteBMPpixelArray(bmpSource.pA);
// }