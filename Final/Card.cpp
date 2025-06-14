#include "Card.h"

// Constructor implementation
Card::Card(string name, int value) {
    setName(name);
    setValue(value);
}

// Mutator implementations with validation
void Card::setName(string name) {
    if (name.empty()) {
        throw runtime_error("Card name cannot be empty");
    }
    cardName = name;
}

void Card::setValue(int value) {
    if (value < 0) {
        throw runtime_error("Card value cannot be negative");
    }
    cardValue = value;
}

// Accessor implementation
string Card::getName() const {
    return cardName;
}

// Operator overloading implementations
ostream& operator<<(ostream& os, const Card& card) {
    os << "Card: " << card.cardName << " (Value: " << card.cardValue << ")";
    return os;
}

istream& operator>>(istream& is, Card& card) {
    string name;
    int value;
    
    cout << "Enter card name: ";
    getline(is, name);
    cout << "Enter card value: ";
    while (!(is >> value) || value < 0) {
        cout << "Invalid input. Please enter a non-negative integer: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    
    card.setName(name);
    card.setValue(value);
    
    return is;
}