#include "Bmputil.hpp"
#include <iostream>
using namespace std;
int main()
{
    int width = 100;
    int height = 100;
    int channel = 3;
    Bmputil bmp;
    // Init Frame Buffer
    unsigned char **FB = bmp.init_image(width, height, channel);
    for (int i = 0; i < width * height; i++)
    {
        FB[i][2] = (unsigned char)i;
    }
    bmp.generate_bmp("file.bmp", width, height, channel, FB);
    free(FB);
    return 0;
}