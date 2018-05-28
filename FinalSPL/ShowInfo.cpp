#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void ReadHeaderAndPrint(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{
    ifstream iFile;
    iFile.open("lighthouse.bmp",ios:: binary);
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature)); // memory allocation problem if signature is in fileHeader.Char and int///////
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));

    //colorTableSize = dibHeader.colorsInColorTable;

    bmpColorTable colorTable;
    iFile.read((char*)&colorTable,sizeof(colorTable));

    iFile.close();

    cout <<"++++++++++++++++BMP Header++++++++++++++\n"<<endl;

    cout <<"+BMP Signature                  : "<<signature.signatureData[0]<<signature.signatureData[1]<<endl;
    cout <<"+BMP file size                  : "<<fileHeader.fileSize<<" bytes"<<endl;
    cout <<"+BMP reserved1                  : "<<fileHeader.reserved1<<endl;
    cout <<"+BMP reserved2                  : "<<fileHeader.reserved2<<endl;
    cout <<"+BMP dataOffset                 : "<<fileHeader.dataOffset<<" bytes"<<endl;

    cout <<"\n++++++++++++++++DIB  Header++++++++++++++\n"<<endl;

    cout <<"+BMP DIB file size              : "<<dibHeader.headerSize<<" bytes"<<endl;
    cout <<"+BMP DIB width                  : "<<dibHeader.width<<" bytes"<<endl;
    cout <<"+BMP DIB height                 : "<<dibHeader.height<<" bytes"<<endl;
    cout <<"+BMP DIB pales                  : "<<dibHeader.planes<<" bytes"<<endl;
    cout <<"+BMP DIB bit per pixel          : "<<dibHeader.bpPixels<<" bytes"<<endl;
    cout <<"+BMP DIB compression            : "<<dibHeader.compression<<" bytes"<<endl;
    cout <<"+BMP DIB image size             : "<<dibHeader.imageSize<<" bytes"<<endl;
    cout <<"+BMP DIB X axis pixel per meter : "<<dibHeader.pixelPerMeterX<<" bytes"<<endl;
    cout <<"+BMP DIB Y axis pixel per meter : "<<dibHeader.pixelPerMeterY<<" bytes"<<endl;
    cout <<"+BMP DIB colorsInColorTable     : "<<dibHeader.colorsInColorTable<<" bytes"<<endl;
    cout <<"+BMP DIB important color Count  : "<<dibHeader.importantcolorCount<<" bytes"<<endl;
    cout <<"+BMP DIB red channel bit mask   : "<<dibHeader.redChannelBitmask<<" bytes"<<endl;
    cout <<"+BMP DIB green channel bit mask : "<<dibHeader.greenChannelBitmask<<" bytes"<<endl;
    cout <<"+BMP DIB blue channel bit mask  : "<<dibHeader.blueChannelBitmask<<" bytes"<<endl;
    cout <<"+BMP DIB alpha channel bit mask : "<<dibHeader.alphaChannelBitmask<<" bytes"<<endl;
    cout <<"+BMP DIB color space type       : "<<dibHeader.colorSpaceType<<" bytes"<<endl;
    cout <<"+BMP DIB color space endpoints  : "<<dibHeader.colorSpaceEnpoints<<" bytes"<<endl;
    cout <<"+BMP DIB gamma for red channel  : "<<dibHeader.gammaForRedChannel<<" bytes"<<endl;
    cout <<"+BMP DIB gamma for green channel: "<<dibHeader.gammaForGreenChannel<<" bytes"<<endl;
    cout <<"+BMP DIB gamma for blue channel : "<<dibHeader.gammaForBlueChannel<<" bytes"<<endl;
    cout <<"+BMP DIB intent                 : "<<dibHeader.intent<<" bytes"<<endl;
    cout <<"+BMP DIB ICC profile Data       : "<<dibHeader.iccProfileData<<" bytes"<<endl;
    cout <<"+BMP DIB ICC profile size       : "<<dibHeader.iccProfileSize<<" bytes"<<endl;
    cout <<"+BMP DIB reserved               : "<<dibHeader.reserved<<" bytes"<<endl;

}
