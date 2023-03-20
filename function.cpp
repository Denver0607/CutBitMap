#include"function.h"
#include "splitBMP.h"

const char* BMP_EXT = ".bmp";

// void makeFile(char *name, const char *extendsion, char* filename, int i, int j) {
// 	char tmp[4] = { i + 49, 'x', j + 49, '\0' };
// 	strcpy(filename, name);
// 	strcat(filename, tmp);
// 	strcat(filename, extendsion);
// }

// void splitBMPFile(char * sourceFile, char * destName, int hsplit, int wsplit)
// {
// 	BMP bmp_src, bmp_dest;
// 	if (!readBMPfile(sourceFile, bmp_src)) return;
// 	int pWidth = bmp_src.dib.width / wsplit;
// 	int pHeight = bmp_src.dib.height / hsplit;
// 	int x, y;
// 	char *destFile = (char*)malloc((strlen(destName + strlen(BMP_EXT)) + 3) * sizeof(char));

// 	x = 0;
// 	for (int i = 0; i < hsplit; i++) {
// 		y = 0;
// 		for (int j = 0; j < wsplit; j++) {
// 			bmp_dest = cutBMPfile(bmp_src, x, y, pHeight, pWidth);
// 			makeFile(destName, BMP_EXT, destFile, i, j);
// 			printBMPfile(destFile, bmp_dest);
// 			delBMPPixelArray(bmp_dest.pA);
// 			y += pWidth;
// 		}
// 		x += pHeight;
// 	}
// 	delBMPPixelArray(bmp_src.pA);
// }

// void makeDestName(char *s, char* cut) {
// 	int start = strlen(s), i = 0;
// 	while (s[start] != '/' && start >=0) start--;
// 	start++;
// 	while (s[start] != '.' && start < strlen(s)) {
// 		cut[i++] = s[start++];
// 		//i++;
// 	}
// 	cut[i] = '\0';
// }

// int StringtoInt(char *s) {
// 	int num = 0;
// 	for (int i = 0; i < strlen(s); i++) {
// 		num = num * 10 + s[i] - '0';
// 	}
// 	return num;
// }

void getDestinationFile(string sourcePath, string destinationPath, int numParts, int partSize, int part, string &destinationFile)
{
    string sourceFile = sourcePath.substr(sourcePath.find_last_of("/\\") + 1);
    destinationFile = destinationPath + '/' + sourceFile;
    if (part < 10)
    {
        destinationFile = destinationFile + ".part0" + to_string(part);
    }
    else
        destinationFile += ".part" + to_string(part);
}