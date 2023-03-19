#include"printBmpFormat.h"

int main(int argc, char* argv[])
{
    string fi = "Pokemon_Omega_Ruby.bmp";
    BMP b;
    bool check;
    ifstream input(fi, ios::binary);
    if (!input)
    {
        cout << "Can't open " << fi << "file!\n";
    }
    readBmpFile(fi, b,check);
    printBMPtoTerminal(b,check);
    deletePixelArray(b.pA);
    input.close();
}
