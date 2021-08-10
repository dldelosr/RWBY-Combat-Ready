#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include "Villain.h"

Villain::Villain() {
    numCards = 0;
    numCardsLeft = 0;
    numEvents = 0;
    vector<Card>newDeck;
    vector<Card>eventsDeck;
    vector<Card>eventsActive;
}
Villain::Villain(const Villain &copy) {
    numCards = copy.numCards;
    numCardsLeft = copy.numCardsLeft;
    numEvents = copy.numEvents;
    vector<Card>newDeck = copy.newDeck;
    vector<Card>eventsDeck = copy.eventsDeck;
    vector<Card>eventsActive = copy.eventsActive;
}
Villain::~Villain() { }

//Auxilliary Function to Check if a String Contains a Specific Substring
bool ContainsSubstring(string ToCheck, string Substring)
{
	if (ToCheck.find(Substring) != string::npos) { return true; }
	return false;
}

//Reads Properly Formatted .txt Files
bool Villain::readTXTFile(const string filename) {
    string stance = "";
    string name = "";
    int speed = -1;
    int damage = -1;
    string type1 = "";
    string type2 = "";
    string effect = "";
    int quantity = -1;
    
    string cardline = "";
    int delimiter = -1;
    Card newCard;
    
    ifstream din;
    din.open(filename);
    
    if (din)
    { 
		while ( getline(din, cardline) ) {
			// cout << cardline << endl;
			delimiter = cardline.find(",");
			stance = cardline.substr(0, delimiter);
			newCard.setStance(stance);
			//cout << stance << endl;
			cardline.erase(0, delimiter + 1);
			
			delimiter = cardline.find(",");
			name = cardline.substr(0, delimiter);
			newCard.setName(name);
			//cout << name << endl;
			cardline.erase(0, delimiter + 1);
			
			delimiter = cardline.find(",");
			//cout << cardline.substr(0, delimiter) << endl;
			speed = stoi(cardline.substr(0, delimiter));
			newCard.setSpeed(speed);
			//cout << speed << endl;
			cardline.erase(0, delimiter + 1);
			
			delimiter = cardline.find(",");
			//cout << cardline.substr(0, delimiter) << endl;
			damage = stoi(cardline.substr(0, delimiter)); // string to int
			newCard.setDamage(damage);
			//cout << damage << endl;
			cardline.erase(0, delimiter + 1);
			
			delimiter = cardline.find(",");
			type1 = cardline.substr(0, delimiter);
			cardline.erase(0, delimiter + 1);
			delimiter = cardline.find(",");
			type2 = cardline.substr(0, delimiter);
			//cout << type1 << " " << type2 << endl;
			cardline.erase(0, delimiter + 1);
			newCard.setTypes(type1, type2);
			
			delimiter = cardline.find(",");
			effect = cardline.substr(0, delimiter);
			newCard.setEffect(effect);
			//cout << effect << endl;
			cardline.erase(0, delimiter + 1);
			
			delimiter = cardline.find(",");
			//cout << cardline.substr(0, delimiter) << endl;
			quantity = stoi(cardline.substr(0, delimiter));
			newCard.setQuantity(quantity);
			//cout << damage << endl;
			cardline.erase(0, delimiter + 1);
			
			//newCard.print();
			for (int i = 0; i < quantity; i++) {
				newDeck.push_back(newCard);
				numCards++;
				//newCard.print();
			}
		}
		din.close();
		return true;
	}
	else
	{
		return false;
	}
}

//Reads Properly Formatted .csv Files
bool Villain::readCSVFile(const string filename) {
	string EmptyColumn = "";
    string CardStance = "";
    string CurrentStance = "";
    string name = "";
    string speedstring = "";
    string damagestring = "";
    int speed = -1;
    int damage = -1;
    string type1 = "";
    string type2 = "";
    string AttackType1 = "";
    string AttackType2 = "";
    string AttackType3 = "";
    string AttackType4 = "";
    string effect = "";
    string effect2 = "";
    int quantity = -1;
    int EventCount = -1;
    int CurrentEvents = 0;
    bool ReadingCards = false;
    bool ReadStance = false;
    bool Type1Found = false;
    bool Type2Found = false;
    bool StancesChecked = false;
    string cardline = "";
    int delimiter = -1;
    Card newCard;
    
    ifstream din;
    din.open(filename);
    
    if (din)
    { 
		while (getline(din, cardline))
		{
			// cout << cardline << endl;
			delimiter = cardline.find(",");
			EmptyColumn = cardline.substr(0, delimiter);
			//cout << stance << endl;
			cardline.erase(0, delimiter + 1);
			
			// cout << cardline << endl;
			delimiter = cardline.find(",");
			CurrentStance = cardline.substr(0, delimiter);
			//Set the Stance of the Cards being Read
			if(CurrentStance.compare("Aggro") == 0 || CurrentStance.compare("Balance") == 0 || CurrentStance.compare("Subtle") == 0 || CurrentStance.compare("Event") == 0)
			{
				CardStance = CurrentStance;
				//cout << "Current stance of cards is " << CardStance << endl;
				ReadingCards = false;
				ReadStance = true;
				//Set the Number of Events if the Next set of Cards are Event Cards
				if(CurrentStance.compare("Event") == 0)
				{
					cardline.erase(0, delimiter + 1);
					delimiter = cardline.find(",");
					EventCount = stoi(cardline.substr(0, delimiter));
					//cout << "Setting number of events to " << EventCount << endl;
					//cout << stance << endl;
					cardline.erase(0, delimiter + 1);
				}
			}
			
			//Record Each Possible Attack Type
			if(CurrentStance.compare("Stance") == 0 && StancesChecked == false)
			{
				//cout << "Determining possible attack types" << endl;
				cardline.erase(0, 31);
				delimiter = cardline.find(",");
				AttackType1 = cardline.substr(0, delimiter);
				//cout << "Type 1: " << AttackType1 << endl;
				cardline.erase(0, delimiter + 1);
				delimiter = cardline.find(",");
				AttackType2 = cardline.substr(0, delimiter);
				//cout << "Type 2: " << AttackType2 << endl;
				cardline.erase(0, delimiter + 1);
				delimiter = cardline.find(",");
				AttackType3 = cardline.substr(0, delimiter);
				//cout << "Type 3: " << AttackType3 << endl;
				cardline.erase(0, delimiter + 1);
				delimiter = cardline.find(",");
				AttackType4 = cardline.substr(0, delimiter);
				//cout << "Type 4: " << AttackType4 << endl;
				cardline.erase(0, delimiter + 1);
				StancesChecked = true;
			}
			cardline.erase(0, delimiter + 1);
			
			if(ReadingCards)
			{
				//Set Stance
				newCard.setStance(CardStance);
				if(CardStance.compare("Event") == 0) { CurrentEvents++; }
				
				//Set Quantity
				delimiter = cardline.find(",");
				//cout << cardline.substr(0, delimiter) << endl;
				quantity = stoi(cardline.substr(0, delimiter));
				newCard.setQuantity(quantity);
				//cout << damage << endl;
				cardline.erase(0, delimiter + 1);
				
				//Set Name
				delimiter = cardline.find(",");
				name = cardline.substr(0, delimiter);
				newCard.setName(name);
				//cout << name << endl;
				cardline.erase(0, delimiter + 1);
				
				//Set Speed
				delimiter = cardline.find(",");
				//cout << cardline.substr(0, delimiter) << endl;
				speedstring = cardline.substr(0, delimiter);
				if(speedstring.size() > 0)
				{
					speed = stoi(speedstring);
					newCard.setSpeed(speed);
					//cout << speed << endl;
				}
				cardline.erase(0, delimiter + 1);
				
				//Set Damage
				delimiter = cardline.find(",");
				//cout << cardline.substr(0, delimiter) << endl;
				damagestring = cardline.substr(0, delimiter); 
				if(damagestring.size() > 0)
				{
					damage = stoi(damagestring);// string to int
					newCard.setDamage(damage);
					//cout << speed << endl;
				}
				//cout << damage << endl;
				cardline.erase(0, delimiter + 1);
				
				//Set Effect
				delimiter = cardline.find(",");
				effect = cardline.substr(0, delimiter);
				if(ContainsSubstring(effect, "\"") == true)
				{
					cardline.erase(0, delimiter + 1);
					delimiter = cardline.find("\"");
					effect2 = cardline.substr(0, delimiter);
					effect.append(effect2);
					newCard.setEffect(effect);
					cardline.erase(0, delimiter + 2);
				}
				else
				{
					newCard.setEffect(effect);
					//cout << effect << endl;
					cardline.erase(0, delimiter + 1);
				}
				if(ContainsSubstring(effect, "\"") == true) { effect.erase(0,1); }
				newCard.setEffect(effect);
				
				
				//Check for Attack Type 1
				delimiter = cardline.find(",");
				type1 = cardline.substr(0, delimiter);
				if(ContainsSubstring(type1, "1")) { type1 = AttackType1; Type1Found = true; }
				cardline.erase(0, delimiter + 1);
				
				//Check for Attack Type 2
				delimiter = cardline.find(",");
				if(Type1Found == false) { type1 = cardline.substr(0, delimiter); }
				else { type2 = cardline.substr(0, delimiter); }
				if(Type1Found == false && ContainsSubstring(type1, "1")) { type1 = AttackType2; Type1Found = true; }
				else if(ContainsSubstring(type2, "1")) { type2 = AttackType2; Type2Found = true; }
				cardline.erase(0, delimiter + 1);
				
				//Check for Attack Type 3
				delimiter = cardline.find(",");
				if(Type1Found == false) { type1 = cardline.substr(0, delimiter); }
				else if(Type2Found == false) { type2 = cardline.substr(0, delimiter); }
				if(Type1Found == false && ContainsSubstring(type1, "1")) { type1 = AttackType3; Type1Found = true; }
				else if(ContainsSubstring(type2, "1")) { type2 = AttackType3; Type2Found = true; }
				cardline.erase(0, delimiter + 1);
				
				//Check for Attack Type 4
				delimiter = cardline.find(",");
				if(Type1Found == false) { type1 = cardline.substr(0, delimiter); }
				else if(Type2Found == false) { type2 = cardline.substr(0, delimiter); }
				if(Type1Found == false && ContainsSubstring(type1, "1") ) { type1 = AttackType4; Type1Found = true; }
				else if(ContainsSubstring(type2, "1")) { type2 = AttackType4; Type2Found = true; }
				cardline.erase(0, delimiter + 1);
				
				//Set Types
				if(Type2Found == false) { type2 = "None"; }
				newCard.setTypes(type1, type2);
				Type1Found = false;
				Type2Found = false;
				
				//newCard.print();
				for (int i = 0; i < quantity; i++)
				{
					newDeck.push_back(newCard);
					numCards++;
					//newCard.print();
				}
			}
			if(ReadStance) { ReadingCards = true; ReadStance = false; }
			if(CurrentEvents == EventCount) { ReadingCards = false; }
		}
		din.close();
		return true;
	}
	else
	{
		return false;
	}
}

//Reads Properly Formatted .tsv Files
bool Villain::readTSVFile(const string filename) {
	string EmptyColumn = "";
    string CardStance = "";
    string CurrentStance = "";
    string name = "";
    string speedstring = "";
    string damagestring = "";
    int speed = -1;
    int damage = -1;
    string type1 = "";
    string type2 = "";
    string AttackType1 = "";
    string AttackType2 = "";
    string AttackType3 = "";
    string AttackType4 = "";
    string effect = "";
    string effect2 = "";
    int quantity = -1;
    int EventCount = -1;
    int CurrentEvents = 0;
    bool ReadingCards = false;
    bool ReadStance = false;
    bool Type1Found = false;
    bool Type2Found = false;
    bool StancesChecked = false;
    string cardline = "";
    int delimiter = -1;
    Card newCard;
    
    ifstream din;
    din.open(filename);
    
    if (din)
    { 
		while (getline(din, cardline))
		{
			// cout << cardline << endl;
			delimiter = cardline.find("\t");
			EmptyColumn = cardline.substr(0, delimiter);
			//cout << stance << endl;
			cardline.erase(0, delimiter + 1);
			
			// cout << cardline << endl;
			delimiter = cardline.find("\t");
			CurrentStance = cardline.substr(0, delimiter);
			//Set the Stance of the Cards being Read
			if(CurrentStance.compare("Aggro") == 0 || CurrentStance.compare("Balance") == 0 || CurrentStance.compare("Subtle") == 0 || CurrentStance.compare("Event") == 0)
			{
				CardStance = CurrentStance;
				//cout << "Current stance of cards is " << CardStance << endl;
				ReadingCards = false;
				ReadStance = true;
				//Set the Number of Events if the Next set of Cards are Event Cards
				if(CurrentStance.compare("Event") == 0)
				{
					cardline.erase(0, delimiter + 1);
					delimiter = cardline.find("\t");
					EventCount = stoi(cardline.substr(0, delimiter));
					//cout << "Setting number of events to " << EventCount << endl;
					//cout << stance << endl;
					cardline.erase(0, delimiter + 1);
				}
			}
			
			//Record Each Possible Attack Type
			if(CurrentStance.compare("Stance") == 0 && StancesChecked == false)
			{
				//cout << "Determining possible attack types" << endl;
				cardline.erase(0, 31);
				delimiter = cardline.find("\t");
				AttackType1 = cardline.substr(0, delimiter);
				//cout << "Type 1: " << AttackType1 << endl;
				cardline.erase(0, delimiter + 1);
				delimiter = cardline.find("\t");
				AttackType2 = cardline.substr(0, delimiter);
				//cout << "Type 2: " << AttackType2 << endl;
				cardline.erase(0, delimiter + 1);
				delimiter = cardline.find("\t");
				AttackType3 = cardline.substr(0, delimiter);
				//cout << "Type 3: " << AttackType3 << endl;
				cardline.erase(0, delimiter + 1);
				delimiter = cardline.find("\t");
				AttackType4 = cardline.substr(0, delimiter);
				//cout << "Type 4: " << AttackType4 << endl;
				cardline.erase(0, delimiter + 1);
				StancesChecked = true;
			}
			cardline.erase(0, delimiter + 1);
			
			if(ReadingCards)
			{
				//Set Stance
				newCard.setStance(CardStance);
				if(CardStance.compare("Event") == 0) { CurrentEvents++; }
				
				//Set Quantity
				delimiter = cardline.find("\t");
				//cout << cardline.substr(0, delimiter) << endl;
				quantity = stoi(cardline.substr(0, delimiter));
				newCard.setQuantity(quantity);
				//cout << damage << endl;
				cardline.erase(0, delimiter + 1);
				
				//Set Name
				delimiter = cardline.find("\t");
				name = cardline.substr(0, delimiter);
				newCard.setName(name);
				//cout << name << endl;
				cardline.erase(0, delimiter + 1);
				
				//Set Speed
				delimiter = cardline.find("\t");
				//cout << cardline.substr(0, delimiter) << endl;
				speedstring = cardline.substr(0, delimiter);
				if(speedstring.size() > 0)
				{
					speed = stoi(speedstring);
					newCard.setSpeed(speed);
					//cout << speed << endl;
				}
				cardline.erase(0, delimiter + 1);
				
				//Set Damage
				delimiter = cardline.find("\t");
				//cout << cardline.substr(0, delimiter) << endl;
				damagestring = cardline.substr(0, delimiter); 
				if(damagestring.size() > 0)
				{
					damage = stoi(damagestring);// string to int
					newCard.setDamage(damage);
					//cout << speed << endl;
				}
				//cout << damage << endl;
				cardline.erase(0, delimiter + 1);
				
				//Set Effect
				delimiter = cardline.find("\t");
				effect = cardline.substr(0, delimiter);
				newCard.setEffect(effect);
				//cout << effect << endl;
				cardline.erase(0, delimiter + 1);
				
				
				//Check for Attack Type 1
				delimiter = cardline.find("\t");
				type1 = cardline.substr(0, delimiter);
				if(ContainsSubstring(type1, "1")) { type1 = AttackType1; Type1Found = true; }
				cardline.erase(0, delimiter + 1);
				
				//Check for Attack Type 2
				delimiter = cardline.find("\t");
				if(Type1Found == false) { type1 = cardline.substr(0, delimiter); }
				else { type2 = cardline.substr(0, delimiter); }
				if(Type1Found == false && ContainsSubstring(type1, "1")) { type1 = AttackType2; Type1Found = true; }
				else if(ContainsSubstring(type2, "1")) { type2 = AttackType2; Type2Found = true; }
				cardline.erase(0, delimiter + 1);
				
				//Check for Attack Type 3
				delimiter = cardline.find("\t");
				if(Type1Found == false) { type1 = cardline.substr(0, delimiter); }
				else if(Type2Found == false) { type2 = cardline.substr(0, delimiter); }
				if(Type1Found == false && ContainsSubstring(type1, "1")) { type1 = AttackType3; Type1Found = true; }
				else if(ContainsSubstring(type2, "1")) { type2 = AttackType3; Type2Found = true; }
				cardline.erase(0, delimiter + 1);
				
				//Check for Attack Type 4
				delimiter = cardline.find("\t");
				if(Type1Found == false) { type1 = cardline.substr(0, delimiter); }
				else if(Type2Found == false) { type2 = cardline.substr(0, delimiter); }
				if(Type1Found == false && ContainsSubstring(type1, "1") ) { type1 = AttackType4; Type1Found = true; }
				else if(ContainsSubstring(type2, "1")) { type2 = AttackType4; Type2Found = true; }
				cardline.erase(0, delimiter + 1);
				
				//Set Types
				if(Type2Found == false) { type2 = "None"; }
				newCard.setTypes(type1, type2);
				Type1Found = false;
				Type2Found = false;
				
				//newCard.print();
				for (int i = 0; i < quantity; i++)
				{
					newDeck.push_back(newCard);
					numCards++;
					//newCard.print();
				}
			}
			if(ReadStance) { ReadingCards = true; ReadStance = false; }
			if(CurrentEvents == EventCount) { ReadingCards = false; }
		}
		din.close();
		return true;
	}
	else
	{
		return false;
	}
}

//Prints the Entire Deck
void Villain::printDeck() {
    for(int i = 0; i < newDeck.size(); i++) {
        newDeck.at(i).print();
    }
}

//Counts the Total Amount of Events Currently in Play
void Villain::countTotalEvents() {
    for(int i = 0; i < newDeck.size(); i++) {
        if (newDeck.at(i).getStance() == "Event") {
            eventsDeck.push_back(newDeck.at(i));
            newDeck.erase(newDeck.begin() + i);
            i--;
            numEvents++;
        }
    }
    //cout << numEvents << endl;
    //for(int i = 0; i < eventsDeck.size(); i++) {
        //eventsDeck.at(i).print();
    //}
}

//Shuffles the Deck with Events Spaced Throughout
void Villain::shuffle() {
    countTotalEvents();
    int numCardsPerEvent = 1 + (numCards / (numEvents + 1));
    //cout << numCardsPerEvent << endl;
    srand(time(NULL));
    random_shuffle(newDeck.begin(), newDeck.end());
    
    // Spaces events throughout deck (but not at the very front or back)
    // Events are front-loaded
    for(int i = 0; i < newDeck.size(); i++) {
        if ((i + 1) % numCardsPerEvent == 0 && eventsDeck.size() > 0) {
            newDeck.insert(newDeck.begin() + i, eventsDeck.at(eventsDeck.size()-1));
            eventsDeck.pop_back();
        }
    }
    //printDeck();
}

//Prompts the User to Either Keep Playing or Quit the Game
string Villain::keepPlaying() {
    string choice = "";
    cout << "Enter anything (enter q to quit, e for active events) to continue.\n";
    cin >> choice;
    cout << endl;
    return choice;
}

//Shows All Currently Active Events
void Villain::showActiveEvents() {
    if (eventsActive.size() <= 0) { cout << "No events currently.\n\n"; }
    else {
        for(int i = 0; i < eventsActive.size(); i++) { eventsActive.at(i).print(); }
    }
}

//Plays the Villain Deck
void Villain::playGame() {
    string choice = "";
    do {
        shuffle();
        if (eventsActive.size() == numEvents) {
            cout << "All cards have been shown. Reshuffled!\n\n";
        }
        for(int i = 0; i < newDeck.size(); i++) {
            if (newDeck.at(i).getStance() == "Event") {
                cout << newDeck.at(i).getStance() << "!\n";
                newDeck.at(i).print();
                eventsActive.push_back(newDeck.at(i));
                newDeck.erase(newDeck.begin() + i);
            }
            else {
                cout << "Stance: " << newDeck.at(i).getStance() << endl;
                choice = keepPlaying();
                while (choice == "E" || choice == "e") {
                    showActiveEvents();
                    choice = keepPlaying();
                }
                if (choice == "Q" || choice == "q") { return; }
                newDeck.at(i).print();
            }
            choice = keepPlaying();
            if (choice == "Q" || choice == "q") { return; }
            while (choice == "E" || choice == "e") {
                    showActiveEvents();
                    choice = keepPlaying();
                }
        }
    } while (!(choice == "Q" || choice == "q"));
}
