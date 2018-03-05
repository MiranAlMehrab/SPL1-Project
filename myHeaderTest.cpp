#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

int height =0;
int width =0;
int jump =0;


struct bmpSignature
{
    unsigned char data[2];
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
void ReadHeader(ifstream &iFile,bmpSignature &sig,bmpHeader &header,bmpDIBHeader &dib,bmpHeightAndzwidth &wAndH)
{
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&sig,sizeof(sig));
    iFile.read((char*)&header,sizeof(header));
    iFile.read((char*)&dib,sizeof(dib));
    iFile.read((char*)&wAndH,sizeof(wAndH));

    iFile.close();
}

void PrintHeader(bmpSignature sig,bmpHeader header,bmpDIBHeader dib,bmpHeightAndzwidth wAndH)
{
    cout <<"++++++++++++++++BMP Header++++++++++++++\n"<<endl;

    cout <<"+BMP Signature : "<<sig.data[0]<<sig.data[1]<<endl;

    cout <<"+BMP file size : "<<header.fileSize<<" bytes"<<endl;
    cout <<"+BMP reserved1 : "<<header.reserved1<<endl;
    cout <<"+BMP reserved2 : "<<header.reserved2<<endl;
    cout <<"+BMP dataOffset: "<<header.dataOffset<<" bytes"<<endl;

    cout <<"+BMP DIB file size : "<<dib.dibHeader<<" bytes"<<endl;
    cout <<"+BMP width size : "<<wAndH.width<<" bytes"<<endl;
    cout <<"+BMP height size : "<<wAndH.height<<" bytes"<<endl;
}


char *data;
char *pixelArray;

void ReadFile(bmpHeightAndzwidth wAndH,bmpHeader header)
{

    ifstream iFile;
    iFile.open("lena.bmp", ios:: binary);

    ofstream oFile;
    oFile.open("lennaCopiedHeader.bmp", ios :: binary);

    int temp =0;
    temp = height + 3;

    jump = header.dataOffset;
    cout << jump <<endl;

    data = new char [temp*width];
    pixelArray = new char [height*width];

    int counter =0;
    int i=0;
    char ch;

    while(!iFile.eof())
    {
        iFile.get(ch);
        data[counter] = ch; //taking all the data to array
        oFile << ch;    //copying  picture


        if(jump<=0 && i<height*width)   //Pixel Array Separating
        {
            pixelArray[i] = ch;
            i++;
        }

        counter++;
        jump--;
    }

    iFile.close();
    oFile.close();

}



int main ()
{
    ifstream iFile;
    iFile.open("lena.bmp",ios:: binary);

    bmpSignature sig;
    bmpHeader header;
    bmpDIBHeader dib;
    bmpHeightAndzwidth wAndH;

    ReadHeader(iFile,sig,header,dib,wAndH);

    PrintHeader(sig,header,dib,wAndH);

    height = wAndH.height;
    width = wAndH.width;

    ReadFile(wAndH,header);


    //int fileSize = ch[2]+ch[3]*pow(2,8)+ch[4]*pow(2,16)+ch[5]*pow(2,24);







    return 0;
}
