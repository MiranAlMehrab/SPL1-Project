#include<iostream>
#include<fstream>
#include <cmath>

#include "HeaderStructure.cpp"
#include "Compression.cpp"
#include "Decompression.cpp"
#include "ShowInfo.cpp"
#include "ImageCopy.cpp"

using namespace std;

int main ()
{

    bmpSignature signature;
    bmpFileHeader fileHeader;
    bmpDIBHeader dibHeader;

    ReadHeaderAndPrint(signature,fileHeader,dibHeader);
    compressImageFile(signature,fileHeader,dibHeader);
    //extractImageFile(signature,fileHeader,dibHeader);
    copyImageFile();

    return 0;
}
