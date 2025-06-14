#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Card {
protected:
    string cardName;
    int cardValue;

public:
    // Constructor
    Card(string name = "", int value = 0);
    
    // Virtual destructor
    virtual ~Card() = default;
    
    // Pure virtual functions (minimum 2 required)
    virtual void display() const = 0;
    virtual int getValue() const = 0;
    
    // Accessor and mutator functions with validation
    void setName(string name);
    void setValue(int value);
    string getName() const;
    
    // Operator overloading (BOTH required)
    friend ostream& operator<<(ostream& os, const Card& card);
    friend istream& operator>>(istream& is, Card& card);
};

#endif // CARD_H