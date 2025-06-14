#include "Deck.h"
#include "PlayingCard.h"

// Constructor implementation with validation
Deck::Deck(int size, string name, string ownr) : maxSize(size), deckName(name), owner(ownr) {
    setMaxSize(size);
    setDeckName(name);
    setOwner(ownr);
}

// Destructor implementation
Deck::~Deck() {
    for (auto card : cards) {
        delete card;
    }
    cards.clear();
}

// Core functionality implementations
void Deck::addCard(Card* card) {
    if (isFull()) {
        throw runtime_error("Deck is full - cannot add more cards");
    }
    if (!card) {
        throw runtime_error("Cannot add null card to deck");
    }
    cards.push_back(card);
}

void Deck::shuffle() {
    if (isEmpty()) {
        throw runtime_error("Cannot shuffle empty deck");
    }
    srand(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < cards.size(); i++) {
        size_t j = rand() % cards.size();
        swap(cards[i], cards[j]);
    }
}

void Deck::displayAllCards() const {
    if (isEmpty()) {
        cout << "Deck is empty." << endl;
        return;
    }
    
    cout << "\n=== " << deckName << " (Owner: " << owner << ") ===" << endl;
    cout << "Cards in deck (" << getCurrentSize() << "/" << maxSize << "):\n" << endl;
    
    for (size_t i = 0; i < cards.size(); i++) {
        cout << "Card " << (i + 1) << ": ";
        cards[i]->display();
        cout << "Value: " << cards[i]->getValue() << endl;
        cout << "-------------------" << endl;
    }
}

Card* Deck::drawCard() {
    if (isEmpty()) {
        throw runtime_error("Cannot draw from empty deck");
    }
    Card* drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

// Accessor and mutator implementations with validation
void Deck::setMaxSize(int size) {
    if (size < 1) {
        throw runtime_error("Deck size must be positive");
    }
    if (size < getCurrentSize()) {
        throw runtime_error("New max size cannot be less than current number of cards");
    }
    maxSize = size;
}

int Deck::getMaxSize() const {
    return maxSize;
}

void Deck::setDeckName(string name) {
    if (name.empty()) {
        throw runtime_error("Deck name cannot be empty");
    }
    deckName = name;
}

string Deck::getDeckName() const {
    return deckName;
}

void Deck::setOwner(string ownr) {
    if (ownr.empty()) {
        throw runtime_error("Owner name cannot be empty");
    }
    owner = ownr;
}

string Deck::getOwner() const {
    return owner;
}

int Deck::getCurrentSize() const {
    return static_cast<int>(cards.size());
}

bool Deck::isEmpty() const {
    return cards.empty();
}

bool Deck::isFull() const {
    return cards.size() >= static_cast<size_t>(maxSize);
}

// File operations with enhanced error handling
void Deck::saveToBinary(const string& filename) {
    if (filename.empty()) {
        throw runtime_error("Filename cannot be empty");
    }
    
    ofstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Could not open file for writing: " + filename);
    }
    
    // Write deck metadata
    int nameLength = deckName.length();
    file.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    file.write(deckName.c_str(), nameLength);
    
    int ownerLength = owner.length();
    file.write(reinterpret_cast<char*>(&ownerLength), sizeof(ownerLength));
    file.write(owner.c_str(), ownerLength);
    
    file.write(reinterpret_cast<char*>(&maxSize), sizeof(maxSize));
    
    // Write number of cards
    int size = getCurrentSize();
    file.write(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Write card data
    for (const auto& card : cards) {
        string name = card->getName();
        int value = card->getValue();
        
        int cardNameLength = name.length();
        file.write(reinterpret_cast<char*>(&cardNameLength), sizeof(cardNameLength));
        file.write(name.c_str(), cardNameLength);
        file.write(reinterpret_cast<char*>(&value), sizeof(value));
    }
    
    if (!file.good()) {
        throw runtime_error("Error occurred while writing to file");
    }
}

void Deck::loadFromBinary(const string& filename) {
    if (filename.empty()) {
        throw runtime_error("Filename cannot be empty");
    }
    
    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Could not open file for reading: " + filename);
    }
    
    // Clear existing cards
    for (auto card : cards) {
        delete card;
    }
    cards.clear();
    
    // Read deck metadata
    int nameLength;
    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
    if (!file.good() || nameLength <= 0 || nameLength > 1000) {
        throw runtime_error("Invalid deck name length in file");
    }
    
    // Fixed: Proper string reading
    vector<char> nameBuffer(nameLength + 1, '\0');
    file.read(nameBuffer.data(), nameLength);
    if (!file.good()) {
        throw runtime_error("Error reading deck name");
    }
    deckName = string(nameBuffer.data(), nameLength);
    
    int ownerLength;
    file.read(reinterpret_cast<char*>(&ownerLength), sizeof(ownerLength));
    if (!file.good() || ownerLength <= 0 || ownerLength > 1000) {
        throw runtime_error("Invalid owner name length in file");
    }
    
    // Fixed: Proper string reading
    vector<char> ownerBuffer(ownerLength + 1, '\0');
    file.read(ownerBuffer.data(), ownerLength);
    if (!file.good()) {
        throw runtime_error("Error reading owner name");
    }
    owner = string(ownerBuffer.data(), ownerLength);
    
    file.read(reinterpret_cast<char*>(&maxSize), sizeof(maxSize));
    if (!file.good()) {
        throw runtime_error("Error reading max size");
    }
    
    // Read number of cards
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    if (!file.good() || size < 0) {
        throw runtime_error("Invalid card count in file");
    }
    
    // Read card data (simplified - creates basic Card objects)
    for (int i = 0; i < size; i++) {
        int cardNameLength;
        file.read(reinterpret_cast<char*>(&cardNameLength), sizeof(cardNameLength));
        if (!file.good() || cardNameLength <= 0 || cardNameLength > 1000) {
            throw runtime_error("Invalid card name length");
        }
        
        // Fixed: Proper string reading for card names
        vector<char> cardNameBuffer(cardNameLength + 1, '\0');
        file.read(cardNameBuffer.data(), cardNameLength);
        if (!file.good()) {
            throw runtime_error("Error reading card name");
        }
        string cardName(cardNameBuffer.data(), cardNameLength);
        
        int value;
        file.read(reinterpret_cast<char*>(&value), sizeof(value));
        if (!file.good()) {
            throw runtime_error("Error reading card value");
        }
        
        // Create a basic PlayingCard (you might want to enhance this)
        PlayingCard* card = new PlayingCard(cardName, value);
        cards.push_back(card);
    }
}

// Operator overloading implementations
ostream& operator<<(ostream& os, const Deck& deck) {
    os << "Deck: " << deck.deckName 
       << " (Owner: " << deck.owner 
       << ", Cards: " << deck.getCurrentSize() 
       << "/" << deck.maxSize << ")";
    return os;
}

istream& operator>>(istream& is, Deck& deck) {
    string name, owner;
    int maxSize;
    
    cout << "Enter deck name: ";
    getline(is, name);
    
    cout << "Enter owner name: ";
    getline(is, owner);
    
    cout << "Enter maximum deck size: ";
    while (!(is >> maxSize) || maxSize < 1) {
        cout << "Invalid input. Please enter a positive integer: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    
    deck.setDeckName(name);
    deck.setOwner(owner);
    deck.setMaxSize(maxSize);
    
    return is;
}