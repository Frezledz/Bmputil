#ifndef _Bmputil_hpp_
#define _Bmputil_hpp_

#include <fstream>
#include <string>
#include <vector>
using namespace std;
// util
void hexStrtoint(string input, vector<unsigned char> &output);
void pushint(int value, int size, vector<unsigned char> &output);

struct Imginfo
{
    int height;
    int channels;
    int width;
};

class Bmputil
{
public:
    int generate_bmp(string name, Imginfo &info, unsigned char **FB)
    {
        vector<unsigned char> header;
        // HEADER
        hexStrtoint("424D", header);
        pushint(info.width * info.height * info.channels + 55, 4, header); // 55+image width*height*(channel count)(+1?)

        hexStrtoint("0000000036000000", header);
        // INFO HEADER
        hexStrtoint("28000000", header);
        pushint(info.width, 4, header);
        pushint(info.height, 4, header);
        hexStrtoint("0100", header);
        pushint(info.channels << 3, 2, header);
        hexStrtoint("00000000", header);
        pushint((info.width * info.height * info.channels), 4, header);
        hexStrtoint("00000000000000000000000000000000", header);
        ofstream file;
        file.open(name, ios::binary);
        for (int i = 0; i < header.size(); i++)
        {
            file.write((char *)&header[i], sizeof(unsigned char));
        }
        for (int i = 0; i < info.width * info.height; i++)
        {
            for (int ii = 0; ii < info.channels; ii++)
            {
                file.write((char *)&(FB[i][ii]), sizeof(char));
            }
        }
        file.close();
        return 0;
    };

    unsigned char **init_image(Imginfo &info)
    {
        unsigned char **FB = (unsigned char **)malloc(sizeof(unsigned char *) * info.width * info.height);
        for (int i = 0; i < info.width * info.height; i++)
        {
            FB[i] = (unsigned char *)malloc(sizeof(unsigned char) * info.channels);
            for (int ii = 0; ii < info.channels; ii++)
            {
                FB[i][ii] = 0; // NULLはよくないな
            }
        }
        return FB;
    };
    void colorize(Imginfo &info, unsigned char **FB, unsigned char B = NULL, unsigned char G = NULL, unsigned char R = NULL, unsigned char A = NULL)
    {
        for (int i = 0; i < (info.width * info.height); i++)
        {
            if (B != NULL)
                FB[i][0] = B;
            if (G != NULL || info.channels > 1)
                FB[i][1] = G;
            if (R != NULL || info.channels > 2)
                FB[i][2] = R;
            if (A != NULL || info.channels > 3)
                FB[i][3] = A;
        }
    }

private:
};

void hexStrtoint(string input, vector<unsigned char> &output)
{
    for (int i = 0; i < input.length(); i += 2)
    {
        string r(input.substr(i, 1) + input.substr(i + 1, 1));
        unsigned int x = stoul(r, nullptr, 16);
        output.push_back((unsigned char)x);
    }
}
void pushint(int value, int size, vector<unsigned char> &output)
{
    for (int i = 0; i < size; i++)
    {
        unsigned int tmp = value & 0xFF;
        value = value >> 8;
        output.push_back((unsigned char)tmp);
    }
}
#endif
