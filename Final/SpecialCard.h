#ifndef SPECIALCARD_H
#define SPECIALCARD_H

#include "Card.h"
#include <sstream>

template<typename T>
class SpecialCard : public Card {
private:
    T specialEffect;
    int durability;
    string cardType;     // Type of special card
    double powerLevel;   // Power level of the effect

public:
    // Constructor
    SpecialCard(string name = "", int value = 0, T effect = T(), int dur = 1, 
                string type = "Magic", double power = 1.0)
        : Card(name, value), specialEffect(effect), durability(dur), 
          cardType(type), powerLevel(power) {
        setDurability(dur);
        setPowerLevel(power);
        setCardType(type);
    }

    // Virtual function implementations
    void display() const override {
        cout << getName() << " (" << cardType << " Card)" << endl;
        cout << "Special Effect: " << specialEffect << endl;
        cout << "Durability: " << durability << ", Power Level: " << powerLevel << endl;
    }

    int getValue() const override {
        return static_cast<int>(cardValue * durability * powerLevel);
    }

    // Accessors and mutators with validation
    void setDurability(int dur) {
        if (dur < 1) {
            throw runtime_error("Durability must be positive");
        }
        durability = dur;
    }

    void setSpecialEffect(const T& effect) {
        specialEffect = effect;
    }

    void setCardType(string type) {
        if (type.empty()) {
            throw runtime_error("Card type cannot be empty");
        }
        cardType = type;
    }

    void setPowerLevel(double power) {
        if (power < 0.1 || power > 10.0) {
            throw runtime_error("Power level must be between 0.1 and 10.0");
        }
        powerLevel = power;
    }

    T getSpecialEffect() const { return specialEffect; }
    int getDurability() const { return durability; }
    string getCardType() const { return cardType; }
    double getPowerLevel() const { return powerLevel; }

    // Operator overloading (BOTH required)
    friend ostream& operator<<(ostream& os, const SpecialCard<T>& card) {
        os << "Special Card: " << card.getName() 
           << " (Type: " << card.cardType 
           << ", Effect: " << card.specialEffect 
           << ", Durability: " << card.durability 
           << ", Power: " << card.powerLevel << ")";
        return os;
    }

    friend istream& operator>>(istream& is, SpecialCard<T>& card) {
        string name, type;
        int value, dur;
        double power;
        T effect;
        
        cout << "Enter card name: ";
        getline(is, name);
        cout << "Enter card value: ";
        is >> value;
        cout << "Enter special effect: ";
        is.ignore();
        getline(is, reinterpret_cast<string&>(effect));
        cout << "Enter durability: ";
        is >> dur;
        cout << "Enter card type: ";
        is.ignore();
        getline(is, type);
        cout << "Enter power level (0.1-10.0): ";
        is >> power;
        
        card.setName(name);
        card.setValue(value);
        card.setSpecialEffect(effect);
        card.setDurability(dur);
        card.setCardType(type);
        card.setPowerLevel(power);
        
        return is;
    }
};

#endif // SPECIALCARD_H