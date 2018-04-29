#include <iostream>
#include <fstream>

using namespace std;


void rleDecompress()
{
    FILE *fp;
    fp=fopen("mirancom.txt","rb");

    FILE *fp1;
    fp1 = fopen("mirancom1.txt","wb");

    unsigned char ch;
    unsigned char num;
    int number;

    while(!feof(fp))
    {

        fread(&ch,1,1,fp);
        fread(&num,1,1,fp);
        number = (int)num;

        for(int i=0;i<number;i++)
        {
            fwrite(&ch,1,1,fp1);
        }
    }

}


int main ()
{
    rleDecompress();
    return 0;
}
