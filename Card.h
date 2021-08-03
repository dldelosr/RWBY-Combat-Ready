#include <iostream>

using namespace std;

class Card {
    private:
        string stance;
        string name;
        int speed;
        int damage;
        string type1; // e.g. melee, ranged
        string type2; // e.g. iajitsu, sometimes none (empty)
        string effect; // e.g. 
        int quantity; // indicates how many copies of particular card
        
    public:
        // Con/destructors
        Card();
        Card(const Card &copy);
        ~Card();
        
        // Mutators
        void setStance(const string stnc);
        void setName(const string nm);
        void setSpeed(const int spd);
        void setDamage(const int dmg);
        void setTypes(const string t1, const string t2);
        void setEffect(const string eff);
        void setQuantity(const int qty);
        
        // Accessors
        string getStance() const;
        string getName() const;
        int getSpeed() const;
        int getDamage() const;
        string getType1() const;
        string getType2() const;
        string getEffect() const;
        int getQuantity() const;
        
        // Print
        void showStance() const;
        void print() const;
};