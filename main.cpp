#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include "Villain.h"

//Auxilliary Function to Check if a String Contains a Specific Substring
bool Contains(string ToCheck, string Substring)
{
	if (ToCheck.find(Substring) != string::npos) { return true; }
	return false;
}

//Auxilliary Function to add Supported Filetype Extensions if the User does not Provide one
string AddExtension(string ToAdd)
{
	string Filetype = "";
	cout << "Please enter the type of the file containing the deck you would like to use." << endl;
	cout << "Currently supported filetypes include '.txt' files." << endl;
	cin >> Filetype;
	while(Filetype.compare(".txt") != 0)
	{
		Filetype = "";
		cout << "The type of file you have entered is not supported, please enter a different filetype or enter q to close the program." << endl;
		cout << "Currently supported filetypes include '.txt' files." << endl;
		cin >> Filetype;
		if (Filetype == "Q" || Filetype == "q") { return "q"; }
	}
	if(Filetype.compare(".txt") == 0) { ToAdd = ToAdd.append(".txt"); }
	return ToAdd;
}

int main()
{
	//Initialization Variables
	string Filename = "";
    Villain newVillain;
    
    //Get Filename, Filetype, and add a file extension to the end if necessary
    cout << "Please enter the name of the file containing the deck you would like to use." << endl;
    cin >> Filename;
    if(Contains(Filename, ".txt") == false)
    {
		Filename = AddExtension(Filename);
		if (Filename == "Q" || Filename == "q") { return 0; }
	}
	
	// Check if the file can be opened
    while (newVillain.readFile(Filename) == false)
    {
		Filename = "";
		cout << "The file you have entered could not be opened, please enter a different filename or enter q to close the program." << endl;
		cin >> Filename;
		if (Filename == "Q" || Filename == "q") { return 0; }
		if(Contains(Filename, ".txt") == false)
		{ 
			Filename = AddExtension(Filename);
			if (Filename == "Q" || Filename == "q") { return 0; }
		}
	}
	
	//Shuffle the deck and play the game
    newVillain.shuffle();
    newVillain.playGame();
}
