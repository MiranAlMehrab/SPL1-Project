#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

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


#define headerSize 1078

char header[headerSize ];
char* body;
int fileSize =0;
int width =0;
int height =0;

int charToInt(char ch)
{
	int iValue = (int) ch;
	if(iValue<0) iValue =iValue + 255;
	return iValue;
}


void readHeightAndWidth()
{

	width = charToInt(header[18])+charToInt(header[19])*pow(2,8)+
			charToInt(header[20])*pow(2,16)+charToInt(header[21])*pow(2,24);
	height = charToInt(header[22])+charToInt(header[23])*pow(2,8)+
			charToInt(header[24])*pow(2,16)+charToInt(header[25])*pow(2,24);
}

void readHeader(ifstream &iFile)
{
	fileSize=0;

	while (!iFile.eof() && fileSize<headerSize )
	{
	    iFile.get(header[fileSize]);
		fileSize++;
	}
}

void createBody()
{
	body = new char[height*width];
}


void readBody(ifstream &iFile)
{
	int bodySize=0;
	while (!iFile.eof())
	{
		fileSize++;
		iFile.get(body[bodySize]);
		bodySize++;
	}
}

void readImage(ifstream &iFile)
{
	readHeader(iFile);
	readHeightAndWidth();
	createBody();
	readBody(iFile);
}

void writeImage(ofstream &oFile)
{
	for(int i=0;i<headerSize;i++)
	{
		oFile << header[i];
	}
	for(int i=0;i<width*height;i++)
	{
		oFile << body[i];
	}
}


void destroyBody()
{
	delete [] body;
}

void readAndWriteHeaderAndBody()
{
    ifstream iFile;
	iFile.open("lenna.bmp", ios::binary);

	ofstream oFile;
	oFile.open("copied.bmp", ios::binary);

	if(iFile.is_open() && oFile.is_open())
	{

		readImage(iFile);
		writeImage(oFile);

		destroyBody();

		iFile.close();
		oFile.close();
	}
	else
	{
		cout << "Could not open file" << endl;
	}
}



int main ()
{

    copyBMP();
    copyBlackAndWhite();
    readAndWriteHeaderAndBody();
















    return 0;
}
