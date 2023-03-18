#include"readBmpFormat.h"

string fi;
ifstream input(fi, ios::binary);

bool isBMP(string fi)
{
    if (!input)
        return 0;

    bmpSignature signature;
    input.seekg(0, ios::cur);
    input.read((char*)&signature, sizeof(bmpSignature));

    return signature.s[0] == 'B' && signature.s[1] == 'M';
}

void readHeaderFormat(string fi, headerFormat& header)
{
    if (!input)
    {
        cout << "Can't open file";
        return;
    }

    input.seekg(0, ios::cur);
    input.read((char*)&header, sizeof(headerFormat));
}

void readDIB(string fi, dibFormat& dib)
{
    if (!input)
    {
        cout << "Can't open file";
        return;
    }

    input.seekg(sizeof(headerFormat), ios::cur);
    input.read((char*)&dib, sizeof(dibFormat));
}

void readPixelLine(string fi, Color*& line, uint32_t length)
{
    if (!input)
    {
        cout << "Can't open file";
        return;
    }

    line = new Color[length];
    input.read((char*)line, sizeof(Color));
}

void skipPadding(string fi, char count)
{
    if (!input)
    {
        cout << "Can't open file";
        return;
    }

    if (count == 0)
        return;

    char padding[3];
    input.read(padding, count);
}

void readPixelArray(string fi, headerFormat header, dibFormat dib, pixelArray& data)
{
    if (!input)
    {
        cout << "Can't open file";
        return;
    }

    data.rowColor = dib.imageHeight;
    data.columnColor = dib.imageWidth;
    data.pixels = new Color * [data.rowColor];

    char paddingCount = (4 - (dib.imageWidth * (dib.imageHeight / 8) % 4)) % 4;

    input.seekg(header.pixelOffset, ios::cur);

    for (int i = 0;i < data.rowColor;i++)
    {
        readPixelLine(fi, data.pixels[data.rowColor - i - 1], data.columnColor);
        skipPadding(fi, paddingCount);
    }
}

void readBmpFile(string fi, BMP &b, bool &check) 
{
    check=1;
    if (!input)
    {
        cout << "Can't open file";
        check=0;
        return;
    }
    if (!isBMP(fi))
    {
        cout << fi << " is not BMP file\n";
        check=0;
        return;
    }
    readHeaderFormat(fi, b.header);
    readDIB(fi, b.dib);
    readPixelArray(fi,b.header,b.dib,b.pA);
    input.close();
    return;
}



