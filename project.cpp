#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

char data[512*514];


bool copyBMP()
{
    ifstream iFile;
    ofstream oFile;
    iFile.open("lenna.bmp", ios::binary);
    oFile.open("Copied.bmp",ios::binary);

    if(iFile.is_open() && oFile.is_open())
    {
        char bit;
        while(!iFile.eof())
        {
            iFile.get(bit);
            oFile<<bit;
        }

        iFile.close();
        oFile.close();

        cout << "File copy is successful!"<<endl;
        return true;
    }
    else
    {
        cout << "File copy failed!"<<endl;
        return false;
    }
}



bool copyBlackAndWhite()
{
    ifstream iFile;
    iFile.open("lenna.bmp", ios::binary);

    ofstream oFile;
    oFile.open("CopiedBlackAndWhite.bmp",ios::binary);

    if(iFile.is_open() && oFile.is_open())
    {
        int counter=0;
        iFile.get(data[counter]);

        while(!iFile.eof())
        {
            counter++;
            iFile.get(data[counter]);
        }

        int sizeOfData = counter+1;
        cout << "Size is: "<<sizeOfData<<endl;

        for(int i=0;i<512*512;i++)
        {
            int iValue = (int) data[counter];
			if(iValue<0) iValue +=255;
			int oValue = 255-iValue;
			char oCharValue = (char) oValue;
			data[counter] = oCharValue;
			counter--;
        }

        for(int j=0;j<sizeOfData;j++)
        {
            oFile << data[j];
        }

        iFile.close();
        oFile.close();

        cout << "File copy is successful!"<<endl;
        return true;
    }
    else
    {
        cout << "File copy failed!"<<endl;
        return false;
    }
}


int main ()
{

    copyBMP();
    copyBlackAndWhite();
















    return 0;
}
