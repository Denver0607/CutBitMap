#include"readBmpFormat.h"

string fi;
ifstream input(fi, ios::binary);

bool isBMP(string fi)
{
    ifstream input(fi, ios::binary);
    if (!input)
        return 0;

    bmpSignature signature;
    input.seekg(0, ios::beg);
    input.read((char*)&signature, sizeof(bmpSignature));
    input.close();
    return signature.s[0] == 'B' && signature.s[1] == 'M';
}

void readHeaderFormat(string fi, headerFormat& header)
{
    ifstream input(fi, ios::binary);
    if (!input)
    {
        cout << "Can't open file to read header\n";
        return;
    }

    input.seekg(0, ios::beg);
    input.read((char*)&header, sizeof(headerFormat));
    input.close();
}

void readDIB(string fi, dibFormat& dib)
{
    ifstream input(fi, ios::binary);
    if (!input)
    {
        cout << "Can't open file to read DIB\n";
        return;
    }

    input.seekg(sizeof(headerFormat), ios::beg);
    input.read((char*)&dib, sizeof(dibFormat));
    input.close();
}

// void readPixelLine(string fi, Color*& line, uint32_t length)
// {
//     ifstream input(fi, ios::binary);
//     if (!input)
//     {
//         cout << "Can't open file\n";
//         return;
//     }

//     line = new Color[length*sizeof(Color)];
//     input.read((char*)line, sizeof(Color)*length);
//     input.close();
// }

void readPixelLine(string fi, Color*& line, uint32_t length)
{
    ifstream input(fi, ios::binary);
    if (!input)
    {
        cout << "Can't open file\n";
        return;
    }

    line = new (nothrow) Color[length];
    if (!line)
    {
        cout << "Failed to allocate memory\n";
        return;
    }
    input.read((char*)line, sizeof(Color));
    input.close();
}

void skipPadding(string fi, char count)
{
    ifstream input(fi, ios::binary);
    if (!input)
    {
        cout << "Can't open file\n";
        return;
    }

    if (count == 0)
        return;

    char padding[3];
    input.read(padding, count);
    input.close();
}

// void readPixelArray(string fi, headerFormat header, dibFormat dib, pixelArray& data)
// {    
//     ifstream input(fi, ios::binary);
//     if (!input)
//     {
//         cout << "Can't open file to read pixel array\n";
//         return;
//     }

//     data.rowColor = dib.imageHeight;
//     data.columnColor = dib.imageWidth;
//     data.pixels = new Color * [data.rowColor];
//     if (!data.pixels)
//     {
//         cout << "Failed to allocate memory for pA\n";
//         return;
//     }

//     char paddingCount = (4 - (dib.imageWidth * (dib.imageHeight / 8) % 4)) % 4;

//     input.seekg(header.pixelOffset, ios::beg);

//     for (int i = 0;i < data.rowColor;i++)
//     {
//         data.pixels[i]=nullptr;
//         readPixelLine(fi, data.pixels[data.rowColor - i - 1], data.columnColor);
//         skipPadding(fi, paddingCount);
//     }
//     input.close();
// }
void readPixelArray(string fi, headerFormat header, dibFormat dib, pixelArray& data)
{    
    ifstream input(fi, ios::binary);
    if (!input)
    {
        cout << "Can't open file to read pixel array\n";
        return;
    }

    data.rowColor = dib.imageHeight;
    data.columnColor = dib.imageWidth;
    data.pixels = new (nothrow) Color * [data.rowColor];
    if (!data.pixels)
    {
        cout << "Failed to allocate memory\n";
        return;
    }

    char paddingCount = (4 - (dib.imageWidth * (dib.imageHeight / 8) % 4)) % 4;

    input.seekg(header.pixelOffset, ios::beg);

    for (int i = 0;i < data.rowColor;i++)
    {
        data.pixels[i] = nullptr; // initialize to null in case allocation fails
        readPixelLine(fi, data.pixels[data.rowColor - i - 1], data.columnColor);
        if (!data.pixels[data.rowColor - i - 1])
        {
            cout << "Failed to allocate memory\n";
            return;
        }
        skipPadding(fi, paddingCount);
    }
    input.close();
}

void readBmpFile(string fi, BMP& b, bool& check)
{
    check = 1;
    ifstream input(fi, ios::binary);
    if (!input)
    {
        cout << "Can't open file\n";
        check = 0;
        return;
    }
    if (!isBMP(fi))
    {
        cout << fi << " is not BMP file\n";
        check = 0;
        return;
    }
    readHeaderFormat(fi, b.header);
    readDIB(fi, b.dib);
    //readPixelArray(fi, b.header, b.dib, b.pA);
    input.close();
    return;
}


