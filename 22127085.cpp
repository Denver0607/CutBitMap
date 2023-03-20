#include"printBmpFormat.h"

int main(int argc, char* argv[])
{
    char * fi = "Pokemon_Omega_Ruby.bmp";
    BMP b;
    bool choice;
    cout << "Do you want to print pixel array?\n (0:no & 1:yes)";
    cin >> choice;
    readBMPfile(fi, b);
    printBMPtoTerminal(b,choice);
    deletePixelArray(b.pA);
}
