#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

unsigned int fileSize =0;
unsigned int height =0;
unsigned int width =0;
unsigned int offset =0;


struct bmpSignature
{
    unsigned char signatureData[2];
};


struct bmpHeader
{
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int dataOffset;
};


struct bmpDIBHeader
{
    unsigned int dibHeader;
};


struct bmpHeightAndzwidth
{
    unsigned int width;
    unsigned int height;
};



void ReadHeader(ifstream &iFile,bmpSignature &signature,bmpHeader &header,bmpDIBHeader &dibHeader,bmpHeightAndzwidth &heightAndWidth)
{
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature));
    iFile.read((char*)&header,sizeof(header));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));
    iFile.read((char*)&heightAndWidth,sizeof(heightAndWidth));

    iFile.close();
}



void PrintHeader(bmpSignature signature,bmpHeader header,bmpDIBHeader dibHeader,bmpHeightAndzwidth heightAndWidth)
{
    cout <<"++++++++++++++++BMP Header++++++++++++++\n"<<endl;

    cout <<"+BMP Signature : "<<signature.signatureData[0]<<signature.signatureData[1]<<endl;

    cout <<"+BMP file size : "<<header.fileSize<<" bytes"<<endl;
    cout <<"+BMP reserved1 : "<<header.reserved1<<endl;
    cout <<"+BMP reserved2 : "<<header.reserved2<<endl;
    cout <<"+BMP dataOffset: "<<header.dataOffset<<" bytes"<<endl;

    cout <<"+BMP DIB file size : "<<dibHeader.dibHeader<<" bytes"<<endl;

    cout <<"+BMP width size : "<<heightAndWidth.width<<" bytes"<<endl;
    cout <<"+BMP height size : "<<heightAndWidth.height<<" bytes"<<endl;

}


void copyBMP()
{
    ifstream iFile;
    iFile.open("barbara.bmp", ios:: binary);

    ofstream oFile;
    oFile.open("barbaraCopy.bmp", ios :: binary);

    char input;
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

bool readFileData()
{

    ifstream iFile;
    iFile.open("barbara.bmp", ios:: binary);

    int Size = 0;
    Size = fileSize + 1;
    fileData = new char [Size];

    if(iFile.is_open())
    {

        for(long int i=0;i<Size;i++)
        {
            fileData[i] = 0;
        }

        char input;
        long int totalCounter =0;

        while(!iFile.eof())
        {
            iFile.get(input);
            fileData[totalCounter] = input;    //taking all the data to array
            totalCounter++;
        }

        iFile.close();
        cout<<"\n+++++++++++++++File data read successful+++++++++++++++"<<endl;
        return true;
    }
    else
    {
        cout <<"\n+++++++++++++++Could not open file+++++++++++++++"<<endl;
        return false;
    }

}


char *pixelData;
bool pixelFlag = false;

bool readPixelData()
{

    ifstream iFile;
    iFile.open("barbara.bmp", ios:: binary);

    int Size = 0;
    Size = (height*width)+1;
    pixelData = new char [Size];

    int counter =0;
    int pixelCounter =0;
    char input;

    if(iFile.is_open())
    {
        while(!iFile.eof())
        {
            iFile.get(input);

            if(counter > offset-1 && pixelCounter < Size+1)   //Pixel Array Separating
            {
                pixelData[pixelCounter] = (char)input;
                pixelCounter++;
            }

            if(pixelCounter == Size) break;
            counter++;

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


void printFileData()
{
    if(fileFlag == true)
    {
        int Size = fileSize+1;
        for(int i=0;i<Size;i++)
        {
            cout << fileData[i];
        }

        cout<<"\n+++++++++++++++File data print successful.++++++++++++++"<<endl;
    }
    else
    {
        cout<<"\n+++++++++++++++Couldn't print file data.++++++++++++++++"<<endl;
    }
}


void printPixelData()
{
    if(pixelFlag == true)
    {
        int Size = (height*width)+1;
        for(int i=0;i<Size;i++)
        {
            cout << pixelData[i];
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

    ifstream iFile;
    iFile.open("barbara.bmp",ios:: binary);

    bmpSignature signature;
    bmpHeader header;
    bmpDIBHeader dibHeader;
    bmpHeightAndzwidth heightAndWidth;

    ReadHeader(iFile,signature,header,dibHeader,heightAndWidth);
    PrintHeader(signature,header,dibHeader,heightAndWidth);

    fileSize = header.fileSize;
    offset = header.dataOffset;
    height = heightAndWidth.height;
    width = heightAndWidth.width;

    //copyBMP();

    //fileFlag = readFileData();
    //printFileData();

    //pixelFlag = readPixelData();
    //printPixelData();

    //freeFileData();
    //freePixelData();

    /*if(fileFlag == true)
    {
        int fileSize1 = fileData[2]+fileData[3]*pow(2,8)+fileData[4]*pow(2,16)+fileData[5]*pow(2,24);
        cout<<fileSize1;
    }*/


    return 0;
}
