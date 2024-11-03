#include "bmpExport.hpp"
#include <iostream>
using namespace std;
int main()
{
    int width = 100;
    int height = 100;
    cout << sizeof(RGB) << endl;
    RGB c = {255, 255, 255};

    BMPexport bmp;
    bmp.generate_bmp("file.bmp", 100, 100, 3);
    return 0;
}