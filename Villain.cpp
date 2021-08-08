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

bool Villain::readFile(const string filename) {
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

void Villain::printDeck() {
    for(int i = 0; i < newDeck.size(); i++) {
        newDeck.at(i).print();
    }
}

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

string Villain::keepPlaying() {
    string choice = "";
    cout << "Enter anything (enter q to quit, e for active events) to continue.\n";
    cin >> choice;
    cout << endl;
    return choice;
}

void Villain::showActiveEvents() {
    if (eventsActive.size() <= 0) { cout << "No events currently.\n\n"; }
    else {
        for(int i = 0; i < eventsActive.size(); i++) { eventsActive.at(i).print(); }
    }
}

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
