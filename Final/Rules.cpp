#include "Rules.h"
#include <algorithm>
#include <iomanip>

// Constructor
Rules::Rules() {
    initializeGameRules();
    initializeCardTypes();
    initializeDeckOperations();
}

// Main rule display functions
void Rules::displayAllRules() const {
    displayHeader("COMPLETE CARD GAME SYSTEM RULES");
    
    displayCardRules();
    cout << endl;
    displayDeckRules();
    cout << endl;
    displayGameplayRules();
    cout << endl;
    displayMenuHelp();
}

void Rules::displayCardRules() const {
    displayHeader("CARD TYPES AND PROPERTIES");
    displaySection("Card Types", cardTypes);
    
    cout << "\nCARD VALUE CALCULATIONS:" << endl;
    cout << "• Playing Cards: Base value × (condition/10)" << endl;
    cout << "• Game Cards: Playing card value × rarity × (foiled ? 3 : 1)" << endl;
    cout << "• Special Cards: Base value × durability × power level" << endl;
    
    cout << "\nCARD PROPERTIES:" << endl;
    cout << "• All cards have: Name, Value" << endl;
    cout << "• Playing cards add: Suit, Face card status, Condition (1-10), Manufacturer" << endl;
    cout << "• Game cards add: Rarity (1-10), Foiled status, Edition, Serial number" << endl;
    cout << "• Special cards add: Special effect, Durability, Card type, Power level (0.1-10.0)" << endl;
}

void Rules::displayDeckRules() const {
    displayHeader("DECK MANAGEMENT RULES");
    displaySection("Deck Operations", deckOperations);
    
    cout << "\nDECK PROPERTIES:" << endl;
    cout << "• Maximum size: 1-200 cards" << endl;
    cout << "• Must have owner name and deck name" << endl;
    cout << "• Supports save/load operations" << endl;
    cout << "• Cards are stored as pointers (polymorphic)" << endl;
}

void Rules::displayGameplayRules() const {
    displayHeader("GAMEPLAY RULES");
    displaySection("Basic Rules", gameRules);
}

void Rules::displayMenuHelp() const {
    displayHeader("MENU COMMANDS HELP");
    
    cout << "1. Add Playing Card    - Create standard playing cards with suits" << endl;
    cout << "2. Add Special Card    - Create cards with special effects and powers" << endl;
    cout << "3. Add Game Card       - Create collectible cards with rarity and foil" << endl;
    cout << "4. Shuffle Deck        - Randomly rearrange all cards in deck" << endl;
    cout << "5. Display All Cards   - Show detailed information for every card" << endl;
    cout << "6. Draw Card from Deck - Remove top card (option to return or keep)" << endl;
    cout << "7. Save Deck to File   - Export deck to binary file (.dat extension)" << endl;
    cout << "8. Load Deck from File - Import deck from binary file" << endl;
    cout << "9. Test Operators      - Demonstrate input/output operator overloading" << endl;
    cout << "10. Display Deck Info  - Show deck statistics and current status" << endl;
    cout << "11. Exit               - Close the program safely" << endl;
}

// Interactive rule browsing
void Rules::browseRules() const {
    int choice;
    do {
        displayHeader("RULES BROWSER");
        cout << "1. View All Rules" << endl;
        cout << "2. Card Type Rules" << endl;
        cout << "3. Deck Management Rules" << endl;
        cout << "4. Gameplay Rules" << endl;
        cout << "5. Menu Commands Help" << endl;
        cout << "6. Search Rules" << endl;
        cout << "7. Return to Main Menu" << endl;
        
        cout << "\nEnter your choice (1-7): ";
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid input. Please enter a number between 1 and 7: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore(); // Clear newline
        
        cout << endl;
        switch(choice) {
            case 1: displayAllRules(); break;
            case 2: displayCardRules(); break;
            case 3: displayDeckRules(); break;
            case 4: displayGameplayRules(); break;
            case 5: displayMenuHelp(); break;
            case 6: {
                string keyword;
                cout << "Enter search keyword: ";
                getline(cin, keyword);
                searchRules(keyword);
                break;
            }
            case 7: cout << "Returning to main menu..." << endl; break;
        }
        
        if (choice != 7) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while (choice != 7);
}

// Search functionality
void Rules::searchRules(const string& keyword) const {
    displayHeader("SEARCH RESULTS FOR: " + keyword);
    
    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
    
    bool found = false;
    
    // Search in game rules
    for (const auto& rule : gameRules) {
        string lowerRule = rule;
        transform(lowerRule.begin(), lowerRule.end(), lowerRule.begin(), ::tolower);
        if (lowerRule.find(lowerKeyword) != string::npos) {
            cout << "• " << rule << endl;
            found = true;
        }
    }
    
    // Search in card types
    for (const auto& type : cardTypes) {
        string lowerType = type;
        transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
        if (lowerType.find(lowerKeyword) != string::npos) {
            cout << "• " << type << endl;
            found = true;
        }
    }
    
    // Search in deck operations
    for (const auto& op : deckOperations) {
        string lowerOp = op;
        transform(lowerOp.begin(), lowerOp.end(), lowerOp.begin(), ::tolower);
        if (lowerOp.find(lowerKeyword) != string::npos) {
            cout << "• " << op << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No rules found containing '" << keyword << "'" << endl;
        cout << "Try searching for: card, deck, value, suit, rarity, foil, or effect" << endl;
    }
}

// Private helper functions
void Rules::initializeGameRules() {
    gameRules = {
        "The Card Game System supports three types of cards: Playing Cards, Special Cards, and Game Cards",
        "Each card has a name and base value that cannot be negative",
        "Cards are managed in decks with configurable maximum sizes (1-200 cards)",
        "Decks can be shuffled, saved to files, and loaded from files",
        "Card values are calculated differently based on card type and properties",
        "The system uses polymorphism to handle different card types uniformly",
        "All user input is validated to prevent errors and invalid data entry",
        "Cards can be drawn from decks and optionally returned",
        "The system supports operator overloading for input and output operations"
    };
}

void Rules::initializeCardTypes() {
    cardTypes = {
        "Playing Card: Traditional cards with suits (Hearts, Diamonds, Clubs, Spades)",
        "Playing Card: Has condition rating (1-10) and manufacturer information",
        "Playing Card: Face cards (Jack, Queen, King) can be designated",
        "Game Card: Collectible cards that extend Playing Cards",
        "Game Card: Features rarity (1-10), foil treatment, edition, and serial numbers",
        "Game Card: Foiled cards are worth 3x more than non-foiled cards", 
        "Special Card: Template-based cards with customizable special effects",
        "Special Card: Has durability, card type, and power level (0.1-10.0)",
        "Special Card: Value calculated as base × durability × power level"
    };
}

void Rules::initializeDeckOperations() {
    deckOperations = {
        "Add Card: Insert new cards into the deck (if not full)",
        "Shuffle: Randomly rearrange all cards using system time as seed",
        "Display All: Show detailed information for every card in the deck",
        "Draw Card: Remove and return the top card from the deck",
        "Save to File: Export deck data to binary file format",
        "Load from File: Import deck data from binary file (replaces current deck)",
        "Deck Info: View current size, maximum size, owner, and deck name",
        "Empty Check: Decks prevent operations when empty (draw, shuffle)",
        "Full Check: Decks prevent adding cards when at maximum capacity"
    };
}

void Rules::displaySection(const string& title, const vector<string>& content) const {
    cout << title << ":" << endl;
    for (const auto& item : content) {
        cout << "• " << item << endl;
    }
}

void Rules::displayHeader(const string& title) const {
    string border(title.length() + 4, '=');
    cout << border << endl;
    cout << "  " << title << "  " << endl;
    cout << border << endl;
}