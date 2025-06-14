#include "PlayingCard.h"

// Constructor implementation with validation
PlayingCard::PlayingCard(string name, int value, string s, bool face, int cond, string manuf) 
    : Card(name, value), faceCard(face) {
    setSuit(s);
    setCondition(cond);
    setManufacturer(manuf);
}

// Virtual function implementations
void PlayingCard::display() const {
    cout << getName() << " of " << suit;
    if (faceCard) cout << " (Face Card)";
    cout << "\nCondition: " << condition << "/10";
    cout << "\nManufacturer: " << manufacturer << endl;
}

int PlayingCard::getValue() const {
    // Condition affects value (poor condition reduces value)
    return static_cast<int>(cardValue * (condition / 10.0));
}

// Mutator implementations with validation
void PlayingCard::setSuit(string s) {
    if (s != "Hearts" && s != "Diamonds" && s != "Clubs" && s != "Spades" && !s.empty()) {
        throw runtime_error("Invalid suit. Must be Hearts, Diamonds, Clubs, or Spades");
    }
    suit = s;
}

void PlayingCard::setFaceCard(bool face) {
    faceCard = face;
}

void PlayingCard::setCondition(int cond) {
    if (cond < 1 || cond > 10) {
        throw runtime_error("Condition must be between 1 and 10");
    }
    condition = cond;
}

void PlayingCard::setManufacturer(string manuf) {
    if (manuf.empty()) {
        throw runtime_error("Manufacturer cannot be empty");
    }
    manufacturer = manuf;
}

// Accessor implementations
string PlayingCard::getSuit() const {
    return suit;
}

bool PlayingCard::isFaceCard() const {
    return faceCard;
}

int PlayingCard::getCondition() const {
    return condition;
}

string PlayingCard::getManufacturer() const {
    return manufacturer;
}

// Operator overloading implementations
ostream& operator<<(ostream& os, const PlayingCard& card) {
    os << card.getName() << " of " << card.suit 
       << " (Value: " << card.getValue() 
       << ", Condition: " << card.condition 
       << ", " << card.manufacturer << ")";
    return os;
}

istream& operator>>(istream& is, PlayingCard& card) {
    string name, suit, manufacturer;
    int value, condition;
    bool face;
    
    cout << "Enter card name: ";
    getline(is, name);
    
    cout << "Enter card value: ";
    while (!(is >> value) || value < 0) {
        cout << "Invalid input. Please enter a non-negative integer: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    
    is.ignore(); // Clear newline
    cout << "Enter suit (Hearts/Diamonds/Clubs/Spades): ";
    getline(is, suit);
    
    cout << "Is it a face card? (1 for yes, 0 for no): ";
    while (!(is >> face)) {
        cout << "Invalid input. Please enter 1 or 0: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    
    cout << "Enter condition (1-10): ";
    while (!(is >> condition) || condition < 1 || condition > 10) {
        cout << "Invalid input. Please enter a number between 1 and 10: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    
    is.ignore(); // Clear newline
    cout << "Enter manufacturer: ";
    getline(is, manufacturer);
    
    card.setName(name);
    card.setValue(value);
    card.setSuit(suit);
    card.setFaceCard(face);
    card.setCondition(condition);
    card.setManufacturer(manufacturer);
    
    return is;
}