#ifndef _Bmputil_hpp_
#define _Bmputil_hpp_

#include <fstream>
#include <string>
#include <vector>
using namespace std;
// util
void hexStrtoint(string input, vector<unsigned char> &output);
void pushint(int value, int size, vector<unsigned char> &output);

struct Image
{
    unsigned char **FB;
    int width;
    int height;
    int channels;
};

class Bmputil
{
public:
    int generate_bmp(string name, int width, int height, int channelcount, unsigned char **FB)
    {
        vector<unsigned char> header;
        // HEADER
        hexStrtoint("424D", header);
        pushint(width * height * channelcount + 55, 4, header); // 55+image width*height*(channel count)(+1?)

        hexStrtoint("0000000036000000", header);
        // INFO HEADER
        hexStrtoint("28000000", header);
        pushint(width, 4, header);
        pushint(height, 4, header);
        hexStrtoint("0100", header);
        pushint(channelcount << 3, 2, header);
        hexStrtoint("00000000", header);
        pushint((width * height * channelcount), 4, header);
        hexStrtoint("00000000000000000000000000000000", header);
        ofstream file;
        file.open(name, ios::binary);
        for (int i = 0; i < header.size(); i++)
        {
            file.write((char *)&header[i], sizeof(unsigned char));
        }
        for (int i = 0; i < width * height; i++)
        {
            for (int ii = 0; ii < channelcount; ii++)
            {
                file.write((char *)&(FB[i][ii]), sizeof(char));
            }
        }
        file.close();
        return 0;
    };

    unsigned char **init_image(int width, int height, int channel)
    {
        unsigned char **FB = (unsigned char **)malloc(sizeof(unsigned char *) * width * height);
        for (int i = 0; i < width * height; i++)
        {
            FB[i] = (unsigned char *)malloc(sizeof(unsigned char) * channel);
            for (int ii = 0; ii < channel; ii++)
            {
                FB[i][ii] = 0; // NULLはよくないな
            }
        }
        return FB;
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
