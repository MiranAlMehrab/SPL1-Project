#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void copyImageFile()
{
    char input;
    ifstream iFile;
    ofstream oFile;


    iFile.open("lighthouse.bmp", ios:: binary);
    oFile.open("CopiedLighthouse.bmp", ios :: binary);

    if(iFile.is_open() && oFile.is_open())
    {
        while(!iFile.eof())
        {
            iFile.get(input);
            oFile<<input;
        }

        iFile.close();
        oFile.close();

        cout <<"\n++++++++++++BMP file copy successful!+++++++++++++"<<endl;
    }
    else
    {
        cout <<"\n+++++++++++++++Couldn't open file.+++++++++++++++"<<endl;
    }
}
