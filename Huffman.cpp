#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#define mximumTreeHeight 100

using namespace std;


char ch;
char arr[256];
int freq[256]={0},varity=0;
char flag [256]={false};
string str;


vector<char>ans;
int n=0;

bool tag=false;

struct properties
{
    char ch;
    string code;
    int codeLen;
};

vector<properties>:: iterator it;
vector<properties>store;

string ss(int n)
{

    stringstream iss;
    iss<<n;
    string str;
    iss>>str;

    return str;
}

vector<char>check;

void charToBinary(char c)
{
    for (int i = 7; i >= 0; --i)
    {
         check.push_back(((c & (1 << i))? '1' : '0'));
    }
}

int binaryToDecimal(int n)
{
    int num = n;
    int decimalValue = 0;

    int base = 1; // Initializing base value to 1, i.e 2^0

    int temp = num;
    while (temp)
    {
        int lastDigit = temp % 10;
        temp = temp/10;

        decimalValue += lastDigit*base;
        base = base*2;
    }

    return decimalValue;
}


string charToString(char ch)
{

    stringstream iss;
    string str;
    iss<<ch;
    iss>>str;

    return str;
}


int stringToNum(string ch)
{
    stringstream iss;
    int sr;
    iss<<ch;
    iss>>sr;

    return sr;
}

struct Node
{
    char data;
    unsigned int freq;
    struct Node *left, *right;
};


struct MinHeap
{
    unsigned int heapSize;
    unsigned int capacity;
    struct Node** nodeArray;
};



struct Node* createNode(char data, unsigned freq)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}



struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    minHeap->heapSize = 0;
    minHeap->capacity = capacity;
    minHeap->nodeArray = (struct Node**)malloc(minHeap->capacity * sizeof(struct Node*));

    return minHeap;
}

void swapMinHeapNode(struct Node** a,struct Node** b)
{
    struct Node* temp;
    temp  = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinHeap* minHeap, int index)
{
    int smallest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;

    if (left < minHeap->heapSize && minHeap->nodeArray[left]->freq < minHeap->nodeArray[smallest]->freq)
        smallest = left;

    if (right < minHeap->heapSize && minHeap->nodeArray[right]->freq < minHeap->nodeArray[smallest]->freq)
        smallest = right;

    if (smallest != index)
    {
        swapMinHeapNode(&minHeap->nodeArray[smallest],&minHeap->nodeArray[index]);
        minHeapify(minHeap, smallest);
    }
}

int checkSize(struct MinHeap* minHeap)
{
    return (minHeap->heapSize == 1);
}

struct Node* extractMin(struct MinHeap* minHeap)
{

    struct Node* temp = minHeap->nodeArray[0];

    minHeap->nodeArray[0] = minHeap->nodeArray[minHeap->heapSize - 1];
    --minHeap->heapSize;
    minHeapify(minHeap, 0);

    return temp;
}


void insertMinHeap(struct MinHeap* minHeap,struct Node* minHeapNode)
{
    ++minHeap->heapSize;
    int i = minHeap->heapSize - 1;

    while (i && minHeapNode->freq < minHeap->nodeArray[(i - 1) / 2]->freq)
    {
        minHeap->nodeArray[i] = minHeap->nodeArray[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->nodeArray[i] = minHeapNode;
}


void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->heapSize - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
    {
        minHeapify(minHeap, i);
    }

}

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        cout<<arr[i];
    }
    cout << endl;
}

int isLeaf(struct Node* root)
{
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
    {
        minHeap->nodeArray[i] = createNode(data[i], freq[i]);
    }

    minHeap->heapSize = size;
    buildMinHeap(minHeap);

    return minHeap;
}

struct Node* buildHuffmanTree(char data[], int freq[], int size)
{
    struct Node *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!checkSize(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(struct Node* root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root))
    {

        cout<<"\t"<<root->data<<" :----->";
        printArray(arr, top);

        properties temp;
        temp.ch = root->data;
        temp.code="";
        for (int i = 0; i < top; ++i)
        {
            temp.code+=ss(arr[i]);
        }
        temp.codeLen = temp.code.length();
        store.push_back(temp);

    }
}

void Huffman(char data[], int freq[], int size)
{
    struct Node* root = buildHuffmanTree(data, freq, size);
    int arr[mximumTreeHeight], top = 0;

    cout<<endl<<"\t\t"<<"Huffman Value"<<endl<<endl;
    printCodes(root, arr, top);
}



void compress()
{
    ifstream inputFile;
    inputFile.open("huffman.txt");

    ofstream outputFile;
    outputFile.open("huffmantext.txt");

    cout<<"\nHuffman compression starting\n\n"<<endl;

    while(getline(inputFile,str))
    {
        //str = str + "\n";
        for(int i=0;i<str.length();i++)
        {
            ch=str[i];
            arr[(int)ch] = ch;
            freq[(int)ch] = freq[(int)ch]+1;
            if(flag[(int)ch]==false)
            {
                flag[(int)ch] = true;
                varity++;
            }
        }
    }



    char vec[varity];
    int vecin[varity];
    int k=0;

    for(int i=0;i<256;i++)
    {
       if(freq[i]>0)
       {
            vec[k]=(arr[i]);
            vecin[k] = freq[i];
            k++;
            cout<<"\t"<<arr[i]<<"   finds ----->"<<freq[i]<<"  times  "<<endl;
        }
    }

    Huffman(vec, vecin, varity);

    vector<char>:: iterator c;

    inputFile.close();

    ifstream inputFile2;
    inputFile2.open("huffman.txt");

    while(getline(inputFile2,str))
    {
        //str = str+"\n";
        for(int i=0;i<str.length();i++)
        {
            ch=str[i];
            for(it=store.begin();it!=store.end();it++){

                properties temp = *it;
                if(temp.ch==ch)
                {
                    for(int i=0;i<temp.codeLen;i++)
                    {
                        ans.push_back(temp.code[i]);
                    }
                    break;
                }

            }
        }
    }

    if(ans.size()%8!=0)
    {
        for(int j=(ans.size()%8);j<8;j++)
        {
            ans.push_back('0');
        }
    }


    string num="";
    int i=0;
    char ch1;


    k=0;
    for(c = ans.begin(); c!=ans.end();c++)
    {
        i++;
        num+=(charToString(*c));
        if(i%8==0)
        {
            k++;
            ch1 = binaryToDecimal(stringToNum(num));
            outputFile<<ch1;

            num="";
        }
    }

    inputFile2.close();
    outputFile.close();

    cout<<"\n\nHuffman compression finishes.\n\n"<<endl;

}

void decompress()
{
    ifstream inputFile;
    inputFile.open("huffmantext.txt");
    char s1;
    int k=0;
    string str="";
    int n3 = ans.size();

    while(inputFile>>s1)
    {
        k++;
        charToBinary(s1);

        str="";
    }

    vector<char>:: iterator c;

    cout<<"\ndecompression is starting using Huffman encoding algorithm\n"<<endl;

    ofstream outputFile;
    outputFile.open("huffmanout.txt");
    string val="";
    string num="";
    k=0;
    ch=0;
    char ct;

    //for(c = ans.begin();c!=ans.end();c++)


    for(c = check.begin();c!=check.end();c++)
    {
        num+=(charToString(*c));
        for(it=store.begin();it!=store.end();it++)
        {

            properties temp;
            temp = *it;
            if(temp.code==num)
            {
                outputFile<<temp.ch;
                if(temp.ch == '.')outputFile<<'\n';
                cout<<temp.ch;
                num="";
            }
        }
    }

    cout <<"\n\nDecompression finishes using Huffman encoding\n"<<endl;


}



int main()
{
    compress();
    decompress();

    return 0;
}
