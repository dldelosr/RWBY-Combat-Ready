#include "Card.h"

Card::Card() {
    stance = "";
    name = "";
    speed = -1;
    damage = -1;
    type1 = "";
    type2 = "";
    effect = "";
    quantity = -1;
}

Card::Card(const Card &copy) {
    stance = copy.stance;
    name = copy.name;
    speed = copy.speed;
    damage = copy.damage;
    type1 = copy.type1;
    type2 = copy.type2;
    effect = copy.effect;
    quantity = copy.quantity;
}

Card::~Card() { }

// Mutators
void Card::setStance(const string stnc) { stance = stnc; }
void Card::setName(const string nm) { name = nm; }
void Card::setSpeed(const int spd) { speed = spd; }
void Card::setDamage(const int dmg) { damage = dmg; }
void Card::setTypes(const string t1, const string t2) {
    type1 = t1;
    type2 = t2;
}
void Card::setEffect(const string eff) { effect = eff; }
void Card::setQuantity(const int qty) { quantity = qty; }

// Accessors
string Card::getStance() const { return stance; }
string Card::getName() const { return name; }
int Card::getSpeed() const { return speed; }
int Card::getDamage() const { return damage; }
string Card::getType1() const { return type1; }
string Card::getType2() const { return type2; }
string Card::getEffect() const { return effect; }
int Card::getQuantity() const { return quantity; }

// Print methods
void Card::showStance() const { cout << "Stance: " << getStance() << endl; }

void Card::print() const {
    // Generating damage number of X's
    if (!(getStance() == "Event")) {
        cout << "(" << getSpeed() << ") "; // Showing speed if not event
        if (getDamage() != 0) { // Showing damage if non-zero
            cout << "[ ";
            for (int i = 0; i < getDamage(); i++) {
                cout << "X ";
            }
            cout << "] ";
        }
    }
    cout << getName() << " ";
    
    // Types
    if (!(getStance() == "Event")) {
        cout << "(" << getType1();
        if (!(getType2() == "None")) {
            cout << ", " << getType2();
        }
        cout << ")"; 
    }
    cout << endl << "Effect: " << getEffect() << endl << endl;
}