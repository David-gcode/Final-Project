#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <filesystem>

class Deck {
private:
    vector<Card*> cards;
    int maxSize;
    string deckName;     // Name/theme of the deck
    string owner;        // Owner of the deck

public:
    // Constructor
    Deck(int size = 52, string name = "Standard Deck", string ownr = "Player");
    
    // Destructor
    ~Deck();
    
    // Core functionality
    void addCard(Card* card);
    void shuffle();
    void displayAllCards() const;
    Card* drawCard();  // Remove and return top card
    
    // Accessors and mutators with validation
    void setMaxSize(int size);
    int getMaxSize() const;
    void setDeckName(string name);
    string getDeckName() const;
    void setOwner(string ownr);
    string getOwner() const;
    int getCurrentSize() const;
    bool isEmpty() const;
    bool isFull() const;
    
    // File operations
    void saveToBinary(const string& filename);
    void loadFromBinary(const string& filename);
    
    // Operator overloading (BOTH required)
    friend ostream& operator<<(ostream& os, const Deck& deck);
    friend istream& operator>>(istream& is, Deck& deck);
};

#endif // DECK_H