#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void extractImageFile(bmpSignature signature,bmpFileHeader fileHeader,bmpDIBHeader dibHeader)
{

    unsigned int fileSize =0;
    unsigned int height =0;
    unsigned int width =0;
    unsigned int offset =0;
    unsigned long int pixelCompressedCounter=0;
    unsigned int colorTableSize =0;

    ifstream iFile;
    ofstream oFile;

    iFile.open("lighthouse.compressed",ios::binary);
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

    cout<<offset<<" "<<height<<endl;
    cout<<pixelCompressedCounter<<endl;

    iFile.open("lighthouse.compressed",ios::binary);
    oFile.open("lighthouseCopy.bmp",ios::binary);
    if(!iFile.is_open() && !oFile.is_open())
    {
        cout <<"\n+++++++++++++++Couldn't open file.+++++++++++++++"<<endl;
        return;
    }


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
                pixelCompressedCounter--;
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
