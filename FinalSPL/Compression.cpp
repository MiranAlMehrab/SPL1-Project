#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

string intToString(unsigned int value)
{

    stringstream strStream;
    string output;

    strStream << value;
    output = strStream.str();

    return output;
}


void compressImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{

    unsigned int fileSize =0;
    unsigned int height =0;
    unsigned int width =0;
    unsigned int offset =0;
    unsigned long int pixelCompressedCounter=0;
    unsigned int colorTableSize =0;

    ifstream iFile;
    ofstream oFile;

    iFile.open("lighthouse.bmp",ios:: binary);
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature));
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));

    fileSize =  fileHeader.fileSize;
    offset   =  fileHeader.dataOffset;
    height   =  dibHeader.height;
    width    =  dibHeader.width;

    iFile.close();

    iFile.open("lighthouse.bmp",ios:: binary);
    oFile.open("lighthouse.compressed",ios::binary);

    if(!iFile.is_open() && !oFile.is_open()) return;

    unsigned char ch;
    unsigned char old;
    unsigned char present;
    unsigned int pixelCounter = 1;
    unsigned long int counter =0;
    unsigned long int limit = (width*height)+offset;

    while(!iFile.eof())
    {
        ch = iFile.get();
        counter++;

        if(counter>offset && counter<limit)
        {
            present = ch;
            if(present == old) pixelCounter++;
            else
            {
                oFile << old;
                if(pixelCounter>1)
                {
                    string str = intToString(pixelCounter);
                    for(int i=0;i<str.length();i++)
                    {
                        oFile <<str[i];
                    }
                }
                pixelCounter = 1;
            }
            old = present;
        }
        else
        {
            oFile<<ch;
            old = ch;
        }

    }
    cout<<"\t"<<pixelCompressedCounter<<endl;
    cout<<"++++++Image Compression Successful.+++++++"<<endl;
}
