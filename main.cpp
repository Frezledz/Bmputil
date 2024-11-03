#include "Bmputil.hpp"
#include <iostream>
using namespace std;
int main()
{
    Imginfo info;
    info.width = 100;
    info.height = 100;
    info.channels = 3;
    Bmputil bmp;
    // Init Frame Buffer
    unsigned char **FB = bmp.init_image(info);
    bmp.colorize(info, FB, 255, 143, 30);
    bmp.generate_bmp("file.bmp", info, FB);
    free(FB);
    return 0;
}