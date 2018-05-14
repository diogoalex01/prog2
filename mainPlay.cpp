#include "dictionaryPlay.h"
#include "boardPlay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

int main()
{
	//variables
	string thesaurusFile, name, savedFile; //file that contains the dictionary
	vector<string> validWords, wordCoordinates, placedWords;
	int rows, columns;
	ifstream fin;

	//OPTION 1
	//--------------------------------------------------------------------------------------------------------------

	cout << endl
		<< "-------------------------" << endl
		<< "CREATE PUZZLE" << endl
		<< "-------------------------" << endl;

	cout << "Thesaurus file name? ";
	cin >> thesaurusFile;

	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n" << endl;
		exit(1);
	}
	cout << "Player name: ";
	cin >> name;
	DictionaryPlay dict(thesaurusFile);

	fin.close();
	cout << endl << "File that cointains a saved board? ";
	cin >> savedFile;

	//--------------------------------------------------------------------------------------------------------------
	
	fin.open(savedFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n" << endl;
		exit(1);
	}

	string next;

	getline(fin, thesaurusFile);

	//extracts the header words to a vector
	while (!fin.eof())
	{
		getline(fin, next);

		if (next.length() > 5)
		{
			//the used method to know where the coordiantes and the words relies on the fact that those two are separatted by 2 spaces
			if ((next.at(3) == ' ') && (next.at(4) == ' '))
			{
				wordCoordinates.push_back(next.substr(0, 3));
				placedWords.push_back(next.substr(5, (next.length() - 5)));
			}
		}
	}

	fin.close();
	//--------------------------------------------------------------------------------------------------------------

	cout << endl << "Board size (rows, columns)? ";
	cin >> rows >> columns;

	BoardPlay brd(rows, columns);
	//brd.upload();

	brd.make();

	//builds
	for (unsigned int j = 0; j < placedWords.size(); j++)
	{
		//rewrites the words that are left in the vector in the board
		brd.insert(wordCoordinates.at(j), placedWords.at(j));
	}

	cout << endl;
	cout << endl;
	brd.fillSpaces();
	brd.show();

	return 0;
}