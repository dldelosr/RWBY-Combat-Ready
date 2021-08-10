#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>
#include "Card.h"

using namespace std;

class Villain {
    private:
        int numCards;
        int numCardsLeft;
        int numEvents;
        vector<Card>newDeck;
        vector<Card>eventsDeck;
        vector<Card>eventsActive;
        // Card allCards[maxCards];
    
    public:
        Villain();
        Villain(const Villain &copy);
        ~Villain();
        
        bool readTXTFile(const string filename);
        bool readCSVFile(const string filename);
        bool readTSVFile(const string filename);
        void printDeck();
        void countTotalEvents();
        void shuffle();
        string keepPlaying();
        void showActiveEvents();
        void playGame();
        
        //void printCard();
};
