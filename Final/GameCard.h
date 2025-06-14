#ifndef GAMECARD_H
#define GAMECARD_H

#include "PlayingCard.h"

class GameCard : public PlayingCard {
private:
    int rarity;          // 1-10 scale
    bool foiled;         // Foil treatment
    string edition;      // Card edition/set
    int serialNumber;    // Unique serial number

public:
    // Constructor
    GameCard(string name = "", int value = 0, string suit = "", bool face = false, 
             int rare = 1, bool foil = false, string ed = "Standard", int serial = 0);
    
    // Accessors and mutators with validation
    void setRarity(int r);
    int getRarity() const;
    void setFoiled(bool foil);
    bool isFoiled() const;
    void setEdition(string ed);
    string getEdition() const;
    void setSerialNumber(int serial);
    int getSerialNumber() const;
    
    // Override display to include all game card info
    void display() const override;
    
    // Override getValue to factor in rarity and foil
    int getValue() const override;
    
    // Operator overloading (BOTH required)
    friend ostream& operator<<(ostream& os, const GameCard& card);
    friend istream& operator>>(istream& is, GameCard& card);
};

#endif // GAMECARD_H