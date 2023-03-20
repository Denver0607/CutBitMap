#include"printBmpFormat.h"
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

void printPixelArray(pixelArray data, char padding)
{
    cout << "------ Pixel Array ------\n";
    for (int i = data.rowColor - 1;i >= 0;i--)
    {
        for (int j = 0;j < data.columnColor;j++)
        {
            cout << data.pixels[j]->blue << data.pixels[j]->green << data.pixels[j]->red;
            while (padding > 0)
            {
                cout << "\0";
                padding--;
            }
        }
    }
}

void printBMPtoTerminal(BMP b)
{
    printBmpHeader(b.header);
    printBmpDib(b.dib);
        // char paddingCount = (4 - (b.dib.imageWidth * (b.dib.imageHeight / 8) % 4)) % 4;
        // printPixelArray(b.pA, paddingCount);
}

// void drawBMP(dibFormat dib, pixelArray data)
// {
//     HWND console=GetConsoleWindow();
//     HDC hdc=GetDC(console);

//     for (int i=0;i<dib.imageHeight;i++)
//     {
//         for (int j=0;j<dib.imageWidth;j++)
//         {
//             Color pixel=data.pixels[i][j];
//             SetPixel(hdc,j,i,RGB(pixel.red,pixel.green,pixel.blue));
//         }
//     }

//     ReleaseDC(console,hdc);
// }


void deletePixelArray(pixelArray data)
{
    for (int i = 0;i < data.rowColor;i++)
    {
        delete[] data.pixels[i];
    }
    delete[]data.pixels;
}



