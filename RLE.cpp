#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}


void rle()
{
    FILE *fp;
    fp=fopen("PixelData.txt","rb");

    FILE *fp1;
    fp1 = fopen("mirancom.txt","wb");

    unsigned char ch;
    unsigned char present;
    unsigned char old;
    unsigned char arr[1000000];

    int counter = 1;
    int i=0;

    while(!feof(fp))
    {

        fread(&ch,1,1,fp);
        //if(ch=='\n')continue;
        arr[i]=(unsigned char )ch;
        i++;
    }
    counter = i;

    /*for(int i=0;i<counter;i++){
        cout<<arr[i];
    }
    cout<<endl;*/
    int n=1;

    for(int i=1;i<counter;i++)
    {

        if(arr[i]==arr[i-1])
        {
           n++;
        }
        else
        {
            // printf("%c%d ",arr[i-1],n);
             unsigned char sh= arr[i-1];
             fwrite(&sh,1,1,fp1);
            // cout<<sh;
             sh = n;
             fwrite(&sh,1,1,fp1);
             //cout<<sh;
             n=1;
        }
    }

   // printf("%c%d ",arr[i-1],n);

}


int main ()
{
    rle();
    return 0;
}
