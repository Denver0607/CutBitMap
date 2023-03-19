#include"printBmpFormat.h"

int main(int argc, char* argv[])
{
    char * fi = "lena.bmp";
    BMP b;
    bool choice;
    // ifstream input(fi, ios::binary);
    // if (!input)
    // {
    //     cout << "Can't open " << fi << "file!\n";
    // }
    // readBmpFile(fi, b,check);
    cout << "Do you want to print pixel array?\n (0:no & 1:yes)";
    cin >> choice;
    readBMPfile(fi, b);
    printBMPtoTerminal(b,choice);
    deletePixelArray(b.pA);
}
