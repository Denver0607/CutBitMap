#include "function.h"
const char* BMP_EXT = ".bmp";

// READ BMP FORMAT
bool isBMP(FILE* f)
{
    if (f == NULL)
        return false;

    bmpSignature s;
    fseek(f, 0, SEEK_SET);
    fread(&s, sizeof(bmpSignature), 1, f);

    if (s.s[0] == 'B' && s.s[1] == 'M')
        return true;
    return false;
}

void readHeaderFormat(FILE* f, headerFormat& header)
{
    if (f == NULL)
        return;

    fseek(f, 0, SEEK_SET);
    fread(&header, sizeof(headerFormat), 1, f);
}

void readDIB(FILE* f, dibFormat& dib)
{
    if (f == NULL)
        return;

    fseek(f, sizeof(headerFormat), SEEK_SET);
    fread(&dib, sizeof(dibFormat), 1, f);
}

void readPixelLine(FILE* f, Color*& line, uint32_t length)
{
    if (f == NULL)
        return;

    line = new Color[length];
    fread(line, sizeof(Color), length, f);
}

void skipPadding(FILE* f, char count)
{
    if (f == NULL)
        return;

    if (count == 0)
        return;

    char padding[3];
    fread(padding, count, 1, f);
}

void readPixelArray(FILE* f, headerFormat header, dibFormat dib, pixelArray& data)
{
    if (f == NULL)
        return;

    data.rowColor = dib.imageHeight;
    data.columnColor = dib.imageWidth;
    data.pixels = new Color * [data.rowColor];
    char paddingCount = (4 - (dib.imageWidth * (dib.colorDepth / 8) % 4)) % 4;

    fseek(f, header.pixelOffset, SEEK_SET);

    for (int i = 0; i < data.rowColor; i++)
    {
        readPixelLine(f, data.pixels[data.rowColor - i - 1], dib.imageWidth);
        skipPadding(f, paddingCount);
    }
}

bool readBMPfile(char* filename, BMP& b)
{
    FILE* f = fopen(filename, "rb");
    if (f == NULL)
    {
        cout << "Can't open file\n";
        return false;
    }

    if (!isBMP(f))
    {
        cout << f << " isn't BMP file\n";
        return false;
    }
    readHeaderFormat(f, b.header);
    readDIB(f, b.dib);
    readPixelArray(f, b.header, b.dib, b.pA);
    fclose(f);

    return true;
}

// PRINT BMP FORMAT TO SCREEN
void printBmpHeader(headerFormat header)
{
    cout << "------ BMP Header ------\n";
    cout << "- File Size: " << header.fileSize << " byte(s)\n";
    cout << "- Reserved1: " << header.reserved1 << endl;
    cout << "- Reserved2: " << header.reserved2 << endl;
    cout << "- Data Offset: " << header.pixelOffset << " byte(s)\n";
}

void printBmpDib(dibFormat dib)
{
    cout << "------ DIB Format ------\n";
    cout << "- DIB Size: " << dib.dibSize << " byte(s)\n";
    cout << "- Image Width: " << dib.imageWidth << endl;
    cout << "- Image Height: " << dib.imageHeight << endl;
    cout << "- Color Planes: " << dib.colorPlanes << endl;
    cout << "- Color Depth: " << dib.colorDepth << endl;
    cout << "- Compression Algorithm: " << dib.compression << endl;
    cout << "- Pixel Array Size: " << dib.pixelArrSize << endl;
    cout << "- Horizontal resolution: " << dib.horizontalPixel << endl;
    cout << "- Vertical resolution: " << dib.verticalPixel << endl;
    cout << "- Number of colors in Color Table: " << dib.numColor << endl;
    cout << "- Number of important colors in Color Table: " << dib.numImportantColor << endl;
}

// PRINT BMP FILE
void printBMPfile(char* fileName, BMP b)
{
    FILE* f = fopen(fileName, "wb");
    if (f == NULL)
        return;
    //print header 
    fseek(f, 0, SEEK_SET);
    fwrite(&b.header, sizeof(headerFormat), 1, f);

    //print dib
    fseek(f, sizeof(headerFormat), SEEK_SET);
    fwrite(&b.dib, sizeof(dibFormat), 1, f);

    //print pixel array
    char paddingCount = (4 - (b.dib.imageWidth * (b.dib.colorDepth / 8) % 4)) % 4;
    char* p = "\0\0\0";
    for (int i = b.pA.rowColor - 1; i >= 0; i--) {
        fwrite(b.pA.pixels[i], sizeof(Color), b.pA.columnColor, f);
        fwrite(p, sizeof(char), paddingCount, f);
    }
    fclose(f);
}

void deleteBMPpixelArray(pixelArray data)
{
    for (int i = 0; i < data.rowColor; i++)
        free(data.pixels[i]);
    free(data.pixels);
}

// CUT BMP FILE
void copyHeader(BMP sourceFile, BMP& destinationFile, uint32_t height, uint32_t width)
{
    destinationFile.header = sourceFile.header;
    char paddingCount = (4 - (width * (sourceFile.dib.colorDepth / 8) % 4)) % 4;
    destinationFile.header.fileSize = (width * sourceFile.dib.colorDepth / 8 + paddingCount) * height + sourceFile.header.pixelOffset;
}

void copyDIB(BMP sourceFile, BMP& destinationFile, uint32_t height, uint32_t width)
{
    destinationFile.dib = sourceFile.dib;
    destinationFile.dib.imageHeight = height;
    destinationFile.dib.imageWidth = width;
    char paddingCount = (4 - (width * (sourceFile.dib.colorDepth / 8) % 4)) % 4;
    destinationFile.dib.pixelArrSize = (width * sourceFile.dib.colorDepth / 8 + paddingCount) * height;
}

BMP cutBmpFile(BMP bmp, uint32_t row, uint32_t column, uint32_t sizeRow, uint32_t sizeColumn)
{
    BMP bResult;
    copyHeader(bmp, bResult, sizeRow, sizeColumn);
    copyDIB(bmp, bResult, sizeRow, sizeColumn);


    pixelArray data = bmp.pA, dataResult;
    dataResult.rowColor = sizeRow;
    dataResult.columnColor = sizeColumn;

    dataResult.pixels = new Color * [sizeRow * sizeof(Color*)];
    for (int i = 0;i < sizeRow;i++)
    {
        dataResult.pixels[i] = new Color[sizeColumn * sizeof(Color)];
        for (int j = 0;j < sizeColumn;j++)
        {
            dataResult.pixels[i][j] = data.pixels[i + row][j + column];
        }
    }
    bResult.pA = dataResult;
    return bResult;
}

// SPLIT BMP FILE
void makeFile(char* name, const char* extendsion, char* filename, int i, int j)
{
    char tmp[4] = { i + 49, 'x', j + 49, '\0' };
    strcpy(filename, name);
    strcat(filename, tmp);
    strcat(filename, extendsion);
}


void makeDestName(char* s, char* cut)
{
    int start = strlen(s), i = 0;
    while (s[start] != '/' && start >= 0)
        start--;
    start++;
    while (s[start] != '.' && start < strlen(s)) 
        cut[i++] = s[start++];
    cut[i] = '\0';
}

void splitBMPfile(char* sourceFile, char* destName, int hsplit, int wsplit)
{
    BMP bmp_src, bmp_dest;
    if (!readBMPfile(sourceFile, bmp_src)) return;
    int pWidth = bmp_src.dib.imageWidth / wsplit;
    int pHeight = bmp_src.dib.imageHeight / hsplit;
    int x, y;
    char* destFile = (char*)malloc(strlen(destName + 7) * sizeof(char));

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


