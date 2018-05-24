#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

unsigned int fileSize =0;
unsigned int height =0;
unsigned int width =0;
unsigned int offset =0;
unsigned long int pixelCompressedCounter=0;
unsigned int colorTableSize =0;



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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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




void compressImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{
    ifstream iFile;
    ofstream oFile;

    iFile.open("lighthouse.bmp",ios:: binary);
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature)); // memory allocation problem if signature is in fileHeader.Char and int///////
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));

    fileSize =  fileHeader.fileSize;
    offset   =  fileHeader.dataOffset;
    height   =  dibHeader.height;
    width    =  dibHeader.width;

    iFile.close();

    iFile.open("lighthouse.bmp",ios:: binary);
    oFile.open("OutputBMP.rle",ios::binary);

    if(!iFile.is_open() && !oFile.is_open()) return;

    unsigned char ch;
    unsigned char old;
    unsigned char present;
    unsigned short int pixelCounter = 1;
    unsigned long int counter =0;
    unsigned long int limit = (width*height)+offset;

    cout<<offset<<"    "<<limit<<endl;

    while(!iFile.eof())
    {
        ch = iFile.get();
        counter++;

        if(counter>offset-1 && counter<limit)
        {
            present = ch;
            if(present == old) pixelCounter++;
            else
            {
                oFile << old;

                char temp = (char)pixelCounter;
                if(pixelCounter>1) oFile << temp; //don't need if value is not more than one.

                pixelCounter = 1;
                pixelCompressedCounter++;
            }
            old = present;
        }
        else
        {
            oFile<<ch;
            old = ch;
        }

    }
    cout<<pixelCompressedCounter<<endl;
}



void extractImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{
    ifstream iFile;
    ofstream oFile;

    iFile.open("outputBMP.rle",ios::binary);
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature)); // memory allocation problem if signature is in fileHeader.Char and int///////
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));
    iFile.close();

    fileSize =  fileHeader.fileSize;
    offset   =  fileHeader.dataOffset;
    height   =  dibHeader.height;
    width    =  dibHeader.width;

    cout<<offset<<" "<<height<<endl;
    cout<<pixelCompressedCounter<<endl;

    iFile.open("outplutBMP.rle",ios::binary);
    oFile.open("BMPDecompress.bmp",ios::binary);
    if(!iFile.is_open() && !oFile.is_open()) return;

    unsigned char ch;
    unsigned char num;
    unsigned short int temp;
    unsigned long int counter=0;

    while(!iFile.eof())
    {
        ch = iFile.get();
        counter++;

        if(counter>offset-1 && pixelCompressedCounter>=0)
        {
            num = iFile.get();
            counter++;

            temp = (int) num;

            cout<<ch;
            cout<<temp;

            for(short int i=0;i<temp;i++)
            {
                oFile<<ch;
            }

            pixelCompressedCounter--;
        }
        else
        {
            oFile<<ch;
            cout<<ch;
        }
    }

}


void cutImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{
    ifstream iFile;
    ofstream oFile;
    iFile.open("bridge.bmp",ios::binary);
    oFile.open("bmpCopy.bmp",ios::binary);

    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature)); // memory allocation problem if signature is in fileHeader.Char and int///////
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));

    /*colorTableSize = dibHeader.colorsInColorTable;
    bmpColorTable colorTable;
    colorTable.colorDefinition = new unsigned int [colorTableSize];
    iFile.read((char*)&colorTable,sizeof(colorTable));
*/
    fileSize =  fileHeader.fileSize;
    offset   =  fileHeader.dataOffset;
    height   =  dibHeader.height;
    width    =  dibHeader.width;


    if(oFile.is_open())
    {
        oFile<<signature.signatureData[0];
        oFile<<signature.signatureData[1];

        oFile<<fileHeader.fileSize;
        oFile<<fileHeader.reserved1;
        oFile<<fileHeader.reserved2;
        oFile<<fileHeader.dataOffset;

        oFile<<dibHeader.headerSize;
        oFile<<dibHeader.width;
        oFile<<dibHeader.height;
        oFile<<dibHeader.planes;
        oFile<<dibHeader.bpPixels;
        oFile<<dibHeader.compression;
        oFile<<dibHeader.imageSize;
        oFile<<dibHeader.pixelPerMeterX;
        oFile<<dibHeader.pixelPerMeterY;
        oFile<<dibHeader.colorsInColorTable;
        oFile<<dibHeader.importantcolorCount;
        oFile<<dibHeader.redChannelBitmask;
        oFile<<dibHeader.greenChannelBitmask;
        oFile<<dibHeader.blueChannelBitmask;
        oFile<<dibHeader.alphaChannelBitmask;
        oFile<<dibHeader.colorSpaceType;
        oFile<<dibHeader.colorSpaceEnpoints;
        oFile<<dibHeader.gammaForRedChannel;
        oFile<<dibHeader.gammaForGreenChannel;
        oFile<<dibHeader.gammaForBlueChannel;
        oFile<<dibHeader.intent;
        oFile<<dibHeader.iccProfileData;
        oFile<<dibHeader.iccProfileSize;
        oFile<<dibHeader.reserved;

        unsigned char ch;
        unsigned int counter=0;

        while(counter<height*width)
        {
            ch = iFile.get();
            oFile << ch;
            counter++;
        }

    }
}


void copyImageFile()
{
    char input;
    ifstream iFile;
    ofstream oFile;

    iFile.open("pepper.bmp", ios:: binary);
    oFile.open("Pepper1.bmp", ios :: binary);

    if(iFile.is_open() && oFile.is_open())
    {
        while(!iFile.eof())
        {
            iFile.get(input);
            oFile<<input;
        }

        iFile.close();
        oFile.close();

        cout <<"\n+++++++++++++++BMP file copy successful!+++++++++++++++"<<endl;
    }
    else
    {
        cout <<"\n+++++++++++++++Couldn't open file. Let alone copy !+++++++++++++++"<<endl;
    }
}






char *fileData;
bool fileFlag = false;

bool storeFileDataIntoText()
{
    ifstream iFile;
    ofstream oFile;

    iFile.open("barbara.bmp", ios:: binary);
    oFile.open("FileData.txt",ios:: binary);

    char data;
    iFile.get(data);

    while(!iFile.eof())
    {
        oFile<<data;
        iFile.get(data);
    }

}


bool storeFileDataIntoArray()
{
    ifstream iFile;
    iFile.open("barbara.bmp", ios:: binary);

    char data;
    unsigned long int counter=0;
    fileData = new char [fileSize];

    while(counter<=fileSize)
    {
        iFile.get(data);
        fileData[counter] = data;
        counter++;
    }
}


void printFileData()
{
    if(fileFlag == true)
    {

        cout<<"Size;;;;;;;;;;;;;;;;;;;;;"<<fileSize<<""<<endl;
        for(unsigned long int i=0;i<fileSize;i++)
        {
            cout << fileData[i];
            if(i%300 == 0)cout<<"++++++++++++++++"<<i<<"++++++++++++++++++"<<endl;
        }

        cout<<"\n+++++++++++++++File data print successful.++++++++++++++"<<endl;
    }
    else
    {
        cout<<"\n+++++++++++++++Couldn't print file data.++++++++++++++++"<<endl;
    }
}

char **pixelData;
bool pixelFlag = false;

bool storePixelDataIntoArray()
{

    //cout << height<<" "<<width<<endl;
    ifstream iFile;
    iFile.open("barbara.bmp", ios:: binary);

    pixelData = new char *[height];
    for(int i=0;i<height;i++)
    {
        pixelData[i] = new char [width];
    }

    unsigned long int i=0;
    unsigned long int j=0;
    unsigned long int counter=0;
    char pixelValue;

    if(iFile.is_open())
    {
        while(!iFile.eof())
        {
            iFile.get(pixelValue);
            counter++;

            if(counter>=offset && i<height)
            {
                if(j<width)
                {
                    pixelData[i][j] = pixelValue;
                    j++;
                }
                else if(j == width)
                {
                    j = 0;
                    i++;
                }
            }
            else if(i == height) break;
        }

        iFile.close();

        cout<<"\n+++++++++++++++Pixel data read successful+++++++++++++++"<<endl;
        return true;
    }
    else
    {
        cout<<"\n+++++++++++++++Couldn't read pixel data.+++++++++++++++"<<endl;
        return false;
    }

}


bool storePixelDataIntoText()
{
    ofstream oFile;
    oFile.open("PixelData.txt");
    if(oFile.is_open())
    {
        for(unsigned long int i=0;i<height;i++)
        {
            for(unsigned long int j=0;j<width;j++)
            {
                oFile << pixelData[i][j];
            }
        }
    }
    else
    {
        cout <<"\n+++++++++++++++Couldn't store pixel data.+++++++++++++++"<<endl;
    }
}




void printPixelData()
{
    if(pixelFlag == true)
    {

        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                cout << pixelData[i][j];
            }
        }

        cout<<"\n+++++++++++++++Pixel data print successful.++++++++++++++"<<endl;
    }
    else
    {
        cout <<"\n+++++++++++++++Couldn't print pixel data.+++++++++++++++"<<endl;
    }
}



void freeFileData()
{
    if(fileFlag == true)
    {
        delete [] fileData;
        cout<<"\n+++++++++++++++File data is deleted.+++++++++++++++"<<endl;
    }
    else
    {
        cout <<"\n+++++++++++++++Couldn't delete file data.+++++++++++++++"<<endl;
    }

}


void freePixelData()
{
    if(pixelFlag == true)
    {
        for(int i=0;i<height;i++)
        {
            delete pixelData[i];
        }
        delete [] pixelData;

        cout<<"\n+++++++++++++++Pixel data is deleted.+++++++++++++++"<<endl;
    }
    else
    {
        cout <<"\n+++++++++++++++Couldn't delete pixel data.+++++++++++++++"<<endl;
    }
}


int main ()
{

    bmpSignature signature;
    bmpFileHeader fileHeader;
    bmpDIBHeader dibHeader;

    ReadHeaderAndPrint(signature,fileHeader,dibHeader);
    //compressImageFile(signature,fileHeader,dibHeader);
    //extractImageFile(signature,fileHeader,dibHeader);
    //cutImageFile(signature,fileHeader,dibHeader);

   // cout <<"+BMP Signature                  : "<<signature.signatureData[0]<<signature.signatureData[1]<<endl;
    //getPictureAttributesValue(fileHeader,dibHeader);

    //copyImageFile();

    //fileFlag = storeFileDataIntoArray();
    //storeFileDataIntoText();
    //printFileData();

    //pixelFlag = storePixelDataIntoArray();
    //storePixelDataIntoText();
    //printPixelData();
    //                            to find out    padding   in bmp            cout <<(4-((3*width)%4))<<endl;
    //freeFileData();
    //freePixelData();

    /*if(fileFlag == true)
    {
        int fileSize1 = fileData[2]+fileData[3]*pow(2,8)+fileData[4]*pow(2,16)+fileData[5]*pow(2,24);
        cout<<fileSize1;
    }*/


    return 0;
}
