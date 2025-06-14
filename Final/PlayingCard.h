#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H

#include "Card.h"

class PlayingCard : public Card {
private:
    string suit;
    bool faceCard;
    int condition;      // 1-10 scale for card condition
    string manufacturer; // Card manufacturer/brand

public:
    // Constructor
    PlayingCard(string name = "", int value = 0, string s = "", bool face = false, 
                int cond = 10, string manuf = "Standard");
    
    // Virtual functions implementation
    void display() const override;
    int getValue() const override;
    
    // Accessors and mutators with validation
    void setSuit(string s);
    string getSuit() const;
    void setFaceCard(bool face);
    bool isFaceCard() const;
    void setCondition(int cond);
    int getCondition() const;
    void setManufacturer(string manuf);
    string getManufacturer() const;
    
    // Operator overloading (BOTH required)
    friend ostream& operator<<(ostream& os, const PlayingCard& card);
    friend istream& operator>>(istream& is, PlayingCard& card);
};

#endif // PLAYINGCARD_H