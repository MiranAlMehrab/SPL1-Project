#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include<fstream>


using namespace std;

struct Node
{
	int index;
	string data;
	Node *next;
};


int stringToInt(string str)
{
    unsigned int num;
    stringstream ss;

    ss << str;
    ss >> num;

    return num;
}



void StartNode(Node *head, int index, string data)
{
	head->index = index;
	head->data = data;
	head->next = NULL;
}


void insertInNode(Node *head, int index, string data)
{
	Node *node = new Node;

	node->index = index;
	node->data = data;
	node->next = NULL;

	Node *current = head;

	while (current != NULL)
	{
		if (current->next == NULL)
		{
			current->next = node;
			return;
		}
		current = current->next;
	}
}




Node *searchNode(Node *head, string data)
{
	Node *current = head;

	while (current != NULL)
	{
		if (data.compare(current->data) == 0)
			return current;
		else
			current = current->next;
	}
	return NULL;
}



Node *searchNode(Node *head, int index)
{
	Node *current = head;

	while (current != NULL)
	{
		if (index == current->index)
			return current;
		else
			current = current->next;
	}
	return NULL;
}





vector <string> split(string str, char delimiter)
{
	vector <string> internalStr;
	stringstream ss(str);
	string taken;

	while (getline(ss, taken, delimiter))
    {
		internalStr.push_back(taken);
	}

	return internalStr;
}


void compressUsingLZ78(ifstream &inputFile, ofstream &outputFile){

	Node *dictionary = new Node;

	int length;
	int lastMatchIndex;
	int index = 1;
    string word;
    string result;

	char input;
	inputFile.get(input);

	word = input;
	StartNode(dictionary, 1, word);
	outputFile << "0," << word;

	while(!inputFile.eof()){
		inputFile.get(input);
		string data;
		data = input;

	again:

		Node *search = searchNode(dictionary, data);

		if (search)
        {
			inputFile.get(input);
			data += input;
			lastMatchIndex = search->index;

			goto again;
		}
		else
		{
			char ch;
			if (input == ' ') ch = '0';
			else ch = input;

			if (data.length() < 2)  outputFile << ' ' << '0'<<',' << ch;
			else outputFile << ' ' << lastMatchIndex << ',' << ch;

			index++;

			insertInNode(dictionary, index, data);
		}
	}
}



void decompressUsingLZ78(ifstream &inputFile, ofstream &outputFile){

        string input = "";
        char ch;

        while(!inputFile.eof())
        {
            ch = inputFile.get();
            input = input+ch;
        }

        inputFile.close();

        Node *dictionary = new Node;
        int index = 2;

		vector <string> spaceSepareted = split(input, ' ');

		for (int i = 0; i < spaceSepareted.size()-1; i++)
		{
			vector <string> comaSeparated = split(spaceSepareted[i], ',');

			if (i == 0)
			{
				StartNode(dictionary, 1, comaSeparated[1]);
				outputFile << comaSeparated[1];
			}
			else
			{
				Node *serched;
				string searchKey = comaSeparated[1];

				serched = searchNode(dictionary, stringToInt(comaSeparated[0]));


				if (serched)
				{
					outputFile << serched->data;
					outputFile << searchKey;
					searchKey = serched->data + split(spaceSepareted[i], ',')[1];

					insertInNode(dictionary, index, searchKey);
				}
				else
				{
					if (stringToInt(comaSeparated[0]) == 0)
                    {
                        insertInNode(dictionary, index, searchKey);
                        outputFile << searchKey;
                    }
					else
                    {

                        outputFile << searchKey;
						insertInNode(dictionary, index, searchKey);
                    }
				}

				index++;
			}
		}
        outputFile.close();

}




int main(){

	string iFileName;
	string oFileName;

	ifstream inputFile;
	ofstream outputFile;

	getline(cin, iFileName);
	getline(cin, oFileName);

	inputFile.open(iFileName.c_str(), ios::binary);
	outputFile.open(oFileName.c_str(), ios::binary);

    //compressUsingLZ78(inputFile, outputFile);
    decompressUsingLZ78(inputFile, outputFile);

	return 0;
}
