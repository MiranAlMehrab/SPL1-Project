#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct bmpSignature
{
    unsigned char signatureData[2];
};


struct bmpFileHeader
{
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int dataOffset;
};

struct bmpDIBHeader
{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bpPixels;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int pixelPerMeterX;
    unsigned int pixelPerMeterY;
    unsigned int colorsInColorTable;
    unsigned int importantcolorCount;
    unsigned int redChannelBitmask;
    unsigned int greenChannelBitmask;
    unsigned int blueChannelBitmask;
    unsigned int alphaChannelBitmask;
    unsigned int colorSpaceType;
    unsigned int colorSpaceEnpoints;
    unsigned int gammaForRedChannel;
    unsigned int gammaForGreenChannel;
    unsigned int gammaForBlueChannel;
    unsigned int intent;
    unsigned int iccProfileData;
    unsigned int iccProfileSize;
    unsigned int reserved;
};

struct bmpColorTable
{
    unsigned int colorDefinition[256];
};
