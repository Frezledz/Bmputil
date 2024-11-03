#include <fstream>
#include <string>
#include <vector>
using namespace std;

void hexStrtoint(string input, vector<unsigned char> &output);
void pushint(int value, int size, vector<unsigned char> &output);
int generate_bmp(string name, int width, int height, int channelcount);
int main()
{
    generate_bmp("file.bmp", 100, 100, 3);
    return 0;
}
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

int generate_bmp(string name, int width, int height, int channelcount)
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
    hexStrtoint("000000001000000000000000000000000000000000000000", header);

    ofstream file;
    file.open(name, ios::binary);
    for (int i = 0; i < header.size(); i++)
    {
        file.write((char *)&header[i], sizeof(unsigned char));
    }
    char B = 0;
    char G = 0;
    char R = 255;
    for (int i = 0; i < width * height; i++)
    {
        file.write((char *)&(B), sizeof(char));
        file.write((char *)&(G), sizeof(char));
        file.write((char *)&(R), sizeof(char));
    }
    file.close();
    return 0;
}