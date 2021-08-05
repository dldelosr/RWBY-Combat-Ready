#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include "Villain.h"

int main()
{
	//Initialization Variables
	string Filename = "";
    Villain newVillain;
    
    //Get Filename and add .txt to the end
    cout << "Please enter the name of the file containing the deck you would like to use." << endl;
    cin >> Filename;
	Filename = Filename.append(".txt");
	
	// Check if the file can be opened
    while (newVillain.readFile(Filename) == false)
    {
		Filename = "";
		cout << "The file you have entered could not be opened, please enter a different filename or enter q to close the program." << endl;
		cin >> Filename;
		Filename = Filename.append(".txt");
		if (Filename == "Q" || Filename == "q") { return 0; }
	}
	
	//Shuffle the deck and play the game
    newVillain.shuffle();
    newVillain.playGame();
}
