#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string.h>

using namespace std;

unsigned int fileSize =0;
unsigned int height =0;
unsigned int width =0;
unsigned int offset =0;
unsigned int colorTableSize =0;
unsigned char specialChar = char(236);


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
};


void ReadHeaderAndPrint(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{
    ifstream iFile;
    iFile.open("crowd.bmp",ios:: binary);
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature));
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));

    iFile.close();

    cout <<"\n++++++++++++++++BMP Header++++++++++++++\n"<<endl;

    cout <<"+BMP Signature                  : "<<signature.signatureData[0]<<signature.signatureData[1]<<endl;
    cout <<"+BMP file size                  : "<<fileHeader.fileSize<<" bytes"<<endl;
    cout <<"+BMP reserved1                  : "<<fileHeader.reserved1<<endl;
    cout <<"+BMP reserved2                  : "<<fileHeader.reserved2<<endl;
    cout <<"+BMP dataOffset                 : "<<fileHeader.dataOffset<<" bytes"<<endl;

    cout <<"\n++++++++++++++++DIB  Header++++++++++++++\n"<<endl;

    cout <<"+BMP DIB file size              : "<<dibHeader.headerSize<<" bytes"<<endl;
    cout <<"+BMP DIB width                  : "<<dibHeader.width<<" bytes"<<endl;
    cout <<"+BMP DIB height                 : "<<dibHeader.height<<" bytes"<<endl;
    cout <<"+BMP DIB pales                  : "<<dibHeader.planes<<endl;
    cout <<"+BMP DIB bit per pixel          : "<<dibHeader.bpPixels<<endl;
    cout <<"+BMP DIB compression            : "<<dibHeader.compression<<endl;
    cout <<"+BMP DIB image size             : "<<dibHeader.imageSize<<" bytes"<<endl;
    cout <<"+BMP DIB X axis pixel per meter : "<<dibHeader.pixelPerMeterX<<endl;
    cout <<"+BMP DIB Y axis pixel per meter : "<<dibHeader.pixelPerMeterY<<endl;
    cout <<"+BMP DIB colorsInColorTable     : "<<dibHeader.colorsInColorTable<<endl;
    cout <<"+BMP DIB important color Count  : "<<dibHeader.importantcolorCount<<endl;

    cout<<endl;

}

string ss(int n){

    string str;
    stringstream iss;

    iss<<n;
    iss>>str;

    return str;

}


void compressImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{
    ifstream iFile;
    ofstream oFile;

    iFile.open("crowd.bmp",ios:: binary);
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





    iFile.open("crowd.bmp",ios:: binary);
    oFile.open("crowd.compressed",ios::binary);

    if(!iFile.is_open() || !oFile.is_open())
    {
        cout<<"++++++++++could not open file.++++++++++++++"<<endl;
        return;
    }


    unsigned char ch;
    unsigned char old;
    unsigned char present;
    unsigned short int pixelCounter = 1;
    unsigned long int counter =0;
    unsigned long int limit = (width*height)+offset;


    while(!iFile.eof())
    {
        ch = iFile.get();
        counter++;

        if(counter>offset && counter<=limit)
        {
            present = ch;
            if(present == old) pixelCounter++;
            else
            {

                if(pixelCounter>1)
                {
                    oFile << old;

                    string str;
                    str = ss(pixelCounter);
                    int n = str.length();

                    char char_array[n+1];
                    strcpy(char_array, str.c_str());

                    for (int i=0; i<n; i++)
                    {
                      oFile << char_array[i];
                    }

                }
                else oFile << old;

                pixelCounter = 1;

            }

            old = present;
        }
        else if(counter == offset)
        {
            old = ch;
        }
        else
        {
            oFile<<ch;
            old = ch;
        }

    }

    oFile.close();

    cout<<"\n+++++++++++++image compression successful.++++++++++++++++\n"<<endl;

}



void extractImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{
    ifstream iFile;
    ofstream oFile;

    iFile.open("crowd.compressed",ios::binary);
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature));

    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));
    iFile.close();


    fileSize =  fileHeader.fileSize;
    offset   =  fileHeader.dataOffset;
    height   =  dibHeader.height;
    width    =  dibHeader.width;


    iFile.open("crowd.compressed",ios::binary);
    oFile.open("crowdCopy.bmp",ios::binary);
    if(!iFile.is_open() && !oFile.is_open()) return;

    unsigned char ch;
    unsigned char num;
    unsigned short int temp;
    unsigned char oldCh;
    unsigned char oldNum;
    unsigned long int counter=0;


   while(!iFile.eof())
    {
        ch = iFile.get();
        oldCh = ch;
        counter++;

        if(counter<=offset)
        {
            oFile<<ch;
        }
        else
        {



            num = iFile.get();
            oldNum = num;

            if(isdigit(num))
            {
                int temp = (int)num;
                for(int i=0;i<temp;i++)
                {
                    oFile<<ch;
                }

            }
            else
            {
                oFile << ch;
                oFile << num;
            }

            counter++;
        }


    }

}




void extract(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{
    ifstream iFile;
    ofstream oFile;

    iFile.open("crowd.compressed",ios::binary);
    if(iFile.eof()) return;

    iFile.seekg(0,ios::beg);
    iFile.read((char*)&signature,sizeof(signature));
    iFile.read((char*)&fileHeader,sizeof(fileHeader));
    iFile.read((char*)&dibHeader,sizeof(dibHeader));

    iFile.close();


    fileSize =  fileHeader.fileSize;
    offset   =  fileHeader.dataOffset;
    height   =  dibHeader.height;
    width    =  dibHeader.width;


    iFile.open("crowd.compressed",ios::binary);
    oFile.open("crowdRestore.bmp",ios::binary);
    if(!iFile.is_open() || !oFile.is_open())
    {
        cout<<"++++++++++could not open file.++++++++++++++"<<endl;
        return;
    }

    unsigned char check;
    unsigned char ch;
    unsigned int num;
    unsigned long int counter=0;
    unsigned char space;
    unsigned int checkCounter;
    unsigned char temp;

    while(!iFile.eof())
    {
        check = iFile.get();
        counter++;

        if(counter>=offset)
        {
            if(check == specialChar)
            {
                checkCounter++;
                while(1)
                {
                    ch = iFile.get();
                    if(ch == specialChar)
                    {
                        checkCounter++;
                        counter++;
                    }
                    else
                    {
                        check = iFile.get();
                        string numString = "";
                        for(int i=0;i<checkCounter;i++)
                        {
                            temp = iFile.get();
                            numString = numString + "temp";

                        }
                        stringstream getNum(numString);
                        getNum >> num;
                        for(int i=0;i<num;i++)
                        {
                            oFile<<check;
                        }
                    }
                }
            }
            else
            {
                oFile << check;
            }
        }
        else oFile << check;

    }

    oFile.close();
}


void copyImageFile()
{
    char input;
    ifstream iFile;
    ofstream oFile;

    iFile.open("crowd.bmp", ios:: binary);
    oFile.open("crowdCopied.bmp", ios :: binary);

    if(iFile.is_open() && oFile.is_open())
    {
        while(!iFile.eof())
        {
            iFile.get(input);
            oFile<<input;
        }

        iFile.close();
        oFile.close();

        cout <<"\n++++++++++++++BMP file copy successful!+++++++++++++++++++\n"<<endl;
    }
    else
    {
        cout <<"\n+++++++++++++++Couldn't open file.+++++++++++++++"<<endl;
    }
}



int main ()
{

    bmpSignature signature;
    bmpFileHeader fileHeader;
    bmpDIBHeader dibHeader;
    int choice =0;

    while(1)
    {
        cout<<"1 for show image info"<<endl;
        cout<<"2 for show compress file"<<endl;
        cout<<"3 for copy image file"<<endl;
        cout<<"4 to exit"<<endl;
        cout<<"Please enter you choice:";
        cin >> choice;

        if(choice == 1) ReadHeaderAndPrint(signature,fileHeader,dibHeader);
        else if(choice == 2)compressImageFile(signature,fileHeader,dibHeader);
        else if(choice == 3)copyImageFile();
        else if(choice ==4) break;
        else cout<<"Enter a valid option"<<endl;

    }
    return 0;
}
