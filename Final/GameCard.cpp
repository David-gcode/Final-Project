#include "GameCard.h"

// Constructor implementation with validation
GameCard::GameCard(string name, int value, string suit, bool face, int rare, bool foil, string ed, int serial)
    : PlayingCard(name, value, suit, face), foiled(foil) {
    setRarity(rare);
    setEdition(ed);
    setSerialNumber(serial);
}

// Mutator implementations with validation
void GameCard::setRarity(int r) {
    if (r < 1 || r > 10) {
        throw runtime_error("Rarity must be between 1 and 10");
    }
    rarity = r;
}

void GameCard::setFoiled(bool foil) {
    foiled = foil;
}

void GameCard::setEdition(string ed) {
    if (ed.empty()) {
        throw runtime_error("Edition cannot be empty");
    }
    edition = ed;
}

void GameCard::setSerialNumber(int serial) {
    if (serial < 0) {
        throw runtime_error("Serial number cannot be negative");
    }
    serialNumber = serial;
}

// Accessor implementations
int GameCard::getRarity() const {
    return rarity;
}

bool GameCard::isFoiled() const {
    return foiled;
}

string GameCard::getEdition() const {
    return edition;
}

int GameCard::getSerialNumber() const {
    return serialNumber;
}

// Override display to include all game card information
void GameCard::display() const {
    cout << getName() << " of " << getSuit();
    if (isFaceCard()) cout << " (Face Card)";
    cout << "\nRarity: " << rarity << "/10";
    if (foiled) cout << " (FOILED)";
    cout << "\nEdition: " << edition;
    cout << "\nSerial Number: " << serialNumber;
    cout << "\nCondition: " << getCondition() << "/10";
    cout << "\nManufacturer: " << getManufacturer() << endl;
}

// Override getValue to factor in rarity, foil, and condition
int GameCard::getValue() const {
    int baseValue = PlayingCard::getValue(); // This includes condition factor
    int multiplier = rarity * (foiled ? 3 : 1); // Foiled cards worth 3x more
    return baseValue * multiplier;
}

// Operator overloading implementations
ostream& operator<<(ostream& os, const GameCard& card) {
    os << card.getName() << " of " << card.getSuit() 
       << " (Rarity: " << card.rarity 
       << ", Edition: " << card.edition
       << ", Serial: " << card.serialNumber;
    if (card.foiled) os << ", FOILED";
    os << ", Value: " << card.getValue() << ")";
    return os;
}

istream& operator>>(istream& is, GameCard& card) {
    string name, suit, manufacturer, edition;
    int value, condition, rarity, serial;
    bool face, foiled;
    
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
    cout << "Condition set to: " << condition << endl;

    is.ignore(); // Clear newline
    cout << "Enter manufacturer: ";
    getline(is, manufacturer);
    
    cout << "Enter rarity (1-10): ";
    while (!(is >> rarity) || rarity < 1 || rarity > 10) {
        cout << "Invalid input. Please enter a number between 1 and 10: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    
    cout << "Is it foiled? (1 for yes, 0 for no): ";
    while (!(is >> foiled)) {
        cout << "Invalid input. Please enter 1 or 0: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    
    is.ignore(); // Clear newline
    cout << "Enter edition: ";
    getline(is, edition);
    
    cout << "Enter serial number: ";
    while (!(is >> serial) || serial < 0) {
        cout << "Invalid input. Please enter a non-negative integer: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    
    card.setName(name);
    card.setValue(value);
    card.setSuit(suit);
    card.setFaceCard(face);
    card.setCondition(condition);
    card.setManufacturer(manufacturer);
    card.setRarity(rarity);
    card.setFoiled(foiled);
    card.setEdition(edition);
    card.setSerialNumber(serial);
    
    return is;
}