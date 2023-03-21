#include"function.h"

int main(int argc, char* argv[])
{
    // Parse the command-line arguments
    char* sourcePath = argv[1];
    int heightSplit = 0, widthSplit = 0;
    BMP bmp;
    char* dest = (char*)malloc((strlen(argv[1]) + 1) * sizeof(char));
    makeDestName(argv[1], dest);

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            heightSplit = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-w") == 0)
        {
            widthSplit = atoi(argv[i + 1]);
        }
    }

    cout << "BMP FIlE FORMAT:\n";
    if (readBMPfile(sourcePath, bmp) == true)
    {
        printBmpHeader(bmp.header);
        printBmpDib(bmp.dib);
        cutBMPfile(argv[1], dest, heightSplit, widthSplit);
    }
}