#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


string intToString(int counter)
{
    string str;
    stringstream ss;
    ss << counter;
    ss >> str;

    return str;

}


int stringToInt(string str)
{
    unsigned int num;
    stringstream ss;

    ss << str;
    ss >> num;

    return num;
}





int main()
{
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open("text.txt");
    outputFile.open("output.txt");

    if(!inputFile.is_open() || !outputFile.is_open())
    {
        cout<<" Error opening file>"<<endl;
        return 0;
    }

    char ch;
    char present;
    char previous;
    unsigned long int counter =0;
    unsigned int charCounter =1;

    while(!inputFile.eof())
    {
        ch = inputFile.get();
        counter++;

        if(counter == 1) previous = ch;
        else
        {
            present = ch;
            if(present == previous) charCounter++;
            else
            {
                outputFile<<previous;
                string str;
                str = intToString(charCounter);
                outputFile<<str;
                outputFile<<',';
                charCounter = 1;
            }

            previous = present;
        }
    }

    inputFile.close();
    outputFile.close();

    inputFile.open("output.txt");
    outputFile.open("outputText.txt");


    string str;
    char num;
    int number;

    while(!inputFile.eof())
    {
        ch = inputFile.get();

        while(1)
        {
            if(inputFile.eof()) goto exit;

            num = inputFile.get();
            if(num == ',')break;

            str = str+num;
        }

        number = stringToInt(str);
        str = "";
        cout<<number<<"     ";
        for(int i=0;i<number;i++)
        {
            outputFile << ch;
        }
        cout<<"writen!"<<endl;

    }

    exit:
        inputFile.close();
        outputFile.close();









    return 0;
}
