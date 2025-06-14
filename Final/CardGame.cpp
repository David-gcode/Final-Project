#include <iostream>
#include <limits>
#include "Card.h"
#include "PlayingCard.h"
#include "SpecialCard.h"
#include "GameCard.h"
#include "Deck.h"
#include "Rules.h"
#include "FileManager.h"

using namespace std;

// Function prototypes for input validation
int getValidInteger(const string& prompt, int min = INT_MIN, int max = INT_MAX);
string getValidString(const string& prompt);
bool getValidBoolean(const string& prompt);
double getValidDouble(const string& prompt, double min = 0.0, double max = 100.0);

int main() {
    try {
        // Create a deck with user input
        cout << "=== Welcome to the Card Game System ===" << endl;
        cout << "First, let's set up your deck:" << endl;
        
        string deckName = getValidString("Enter deck name: ");
        string owner = getValidString("Enter owner name: ");
        int maxSize = getValidInteger("Enter maximum deck size: ", 1, 200);
        
        Deck gameDeck(maxSize, deckName, owner);
        cout << "\nDeck created successfully!" << endl;
        cout << gameDeck << endl;
        
        FileManager fileManager("./saves/"); // Create instance with default save directory
        
        // Interactive menu
        int choice;
        do {
            try {
                cout << "\n=== Card Game Menu ===" << endl;
                cout << "1. Add Playing Card" << endl;
                cout << "2. Add Special Card" << endl;
                cout << "3. Add Game Card" << endl;
                cout << "4. Shuffle Deck" << endl;
                cout << "5. Display All Cards" << endl;
                cout << "6. Draw Card from Deck" << endl;
                cout << "7. File Management Menu" << endl;
                cout << "8. Quick Load Deck" << endl;
                cout << "9. Test Operator Overloading" << endl;
                cout << "10. Display Deck Info" << endl;
                cout << "11. Rules/Help" << endl;
                cout << "12. Exit" << endl;
                
                choice = getValidInteger("Enter your choice: ", 1, 12);
                
                switch(choice) {
                    case 1: {
                        cout << "\n=== Adding Playing Card ===" << endl;
                        
                        // Method 1: Manual input
                        string name = getValidString("Enter card name: ");
                        int value = getValidInteger("Enter card value: ", 0, 1000);
                        
                        cout << "Available suits: Hearts, Diamonds, Clubs, Spades" << endl;
                        string suit = getValidString("Enter suit: ");
                        
                        bool face = getValidBoolean("Is it a face card? (1/0): ");
                        int condition = getValidInteger("Enter condition (1-10): ", 1, 10);
                        string manufacturer = getValidString("Enter manufacturer: ");
                        
                        PlayingCard* card = new PlayingCard(name, value, suit, face, condition, manufacturer);
                        gameDeck.addCard(card);
                        cout << "Playing card added successfully!" << endl;
                        cout << *card << endl;
                        break;
                    }
                    
                    case 2: {
                        cout << "\n=== Adding Special Card ===" << endl;
                        
                        string name = getValidString("Enter card name: ");
                        int value = getValidInteger("Enter card value: ", 0, 1000);
                        string effect = getValidString("Enter special effect: ");
                        int durability = getValidInteger("Enter durability: ", 1, 100);
                        string cardType = getValidString("Enter card type: ");
                        double powerLevel = getValidDouble("Enter power level (0.1-10.0): ", 0.1, 10.0);
                        
                        SpecialCard<string>* card = new SpecialCard<string>(name, value, effect, durability, cardType, powerLevel);
                        gameDeck.addCard(card);
                        cout << "Special card added successfully!" << endl;
                        cout << *card << endl;
                        break;
                    }
                    
                    case 3: {
                        cout << "\n=== Adding Game Card ===" << endl;
                        
                        string name = getValidString("Enter card name: ");
                        int value = getValidInteger("Enter card value: ", 0, 1000);
                        
                        cout << "Available suits: Hearts, Diamonds, Clubs, Spades" << endl;
                        string suit = getValidString("Enter suit: ");
                        
                        bool face = getValidBoolean("Is it a face card? (1/0): ");
                        int condition = getValidInteger("Enter condition (1-10): ", 1, 10);
                        string manufacturer = getValidString("Enter manufacturer: ");
                        int rarity = getValidInteger("Enter rarity (1-10): ", 1, 10);
                        bool foiled = getValidBoolean("Is it foiled? (1/0): ");
                        string edition = getValidString("Enter edition: ");
                        int serialNumber = getValidInteger("Enter serial number: ", 0, 999999);
                        
                        GameCard* card = new GameCard(name, value, suit, face, rarity, foiled, edition, serialNumber);
                        gameDeck.addCard(card);
                        cout << "Game card added successfully!" << endl;
                        cout << *card << endl;
                        break;  // Add this break statement
                    }
                    
                    case 4: {
                        cout << "\n=== Shuffling Deck ===" << endl;
                        gameDeck.shuffle();
                        cout << "Deck shuffled successfully!" << endl;
                        break;
                    }
                    
                    case 5: {
                        cout << "\n=== Displaying All Cards ===" << endl;
                        gameDeck.displayAllCards();
                        break;
                    }
                    
                    case 6: {
                        cout << "\n=== Drawing Card ===" << endl;
                        Card* drawnCard = gameDeck.drawCard();
                        cout << "Card drawn: ";
                        drawnCard->display();
                        cout << "Card value: " << drawnCard->getValue() << endl;
                        
                        // Ask if user wants to keep the card or put it back
                        bool keepCard = getValidBoolean("Keep this card? (1 to keep, 0 to return to deck): ");
                        if (!keepCard) {
                            gameDeck.addCard(drawnCard);
                            cout << "Card returned to deck." << endl;
                        } else {
                            cout << "Card kept. Don't forget to manage its memory!" << endl;
                            delete drawnCard; // Clean up for demo purposes
                        }
                        break;
                    }
                    
                    case 7: {
                        cout << "\n=== File Management ===" << endl;
                        int fileChoice;
                        do {
                            fileManager.displayFileMenu();
                            fileChoice = getValidInteger("Enter your choice: ", 1, 7);
                            
                            switch(fileChoice) {
                                case 1: {
                                    fileManager.listSavedDecks();
                                    break;
                                }
                                case 2: {
                                    if (fileManager.loadSelectedDeck(gameDeck)) {
                                        cout << "Current deck replaced with loaded deck." << endl;
                                        cout << gameDeck << endl;
                                    } else {
                                        cout << "Load operation failed or was cancelled." << endl;
                                    }
                                    break;
                                }
                                case 3: {
                                    fileManager.saveNewDeck(gameDeck);
                                    break;
                                }
                                case 4: {
                                    fileManager.deleteSelectedDeck();
                                    break;
                                }
                                case 5: {
                                    string newDir = getValidString("Enter new save directory path: ");
                                    fileManager.setSaveDirectory(newDir);
                                    cout << "Save directory changed to: " << fileManager.getSaveDirectory() << endl;
                                    break;
                                }
                                case 6: {
                                    fileManager.refreshFileList();
                                    cout << "File list refreshed." << endl;
                                    break;
                                }
                                case 7: {
                                    cout << "Returning to main menu..." << endl;
                                    break;
                                }
                            }
                            
                            if (fileChoice != 7) {
                                cout << "\nPress Enter to continue...";
                                cin.ignore();
                                cin.get();
                            }
                            
                        } while (fileChoice != 7);
                        break;
                    }
                    case 8: {
                        cout << "\n=== Quick Load Deck ===" << endl;
                        string filename = getValidString("Enter filename to load: ");
                        
                        try {
                            gameDeck.loadFromBinary(filename);
                            cout << "Deck loaded successfully from " << filename << endl;
                            cout << gameDeck << endl;
                        } catch (const runtime_error& e) {
                            cout << "Error loading deck: " << e.what() << endl;
                            cout << "Try using the File Management menu (option 7) for better file browsing." << endl;
                        }
                        break;
                    }
                    
                    case 9: {
                        try {
                            cout << "\n=== Testing Operator Overloading ===" << endl;
                            
                            // Test deck output operator
                            cout << "Deck information using << operator:" << endl;
                            cout << gameDeck << endl;
                            
                            // Test creating a card using input operator
                            cout << "\nCreating a new Playing Card using >> operator:" << endl;
                            PlayingCard testCard;
                            cin.ignore(); // Clear any remaining input
                            cin >> testCard;
                            cout << "\nCard created: " << testCard << endl;
                            
                            // Add the card to deck
                            PlayingCard* cardPtr = new PlayingCard(testCard);
                            gameDeck.addCard(cardPtr);
                            cout << "Card added to deck!" << endl;
                        } catch (const exception& e) {
                            cout << "Error during operator testing: " << e.what() << endl;
                        }
                        break;
                    }
                    
                    case 10: {
                        cout << "\n=== Deck Information ===" << endl;
                        cout << gameDeck << endl;
                        cout << "Current size: " << gameDeck.getCurrentSize() << endl;
                        cout << "Max size: " << gameDeck.getMaxSize() << endl;
                        cout << "Is empty: " << (gameDeck.isEmpty() ? "Yes" : "No") << endl;
                        cout << "Is full: " << (gameDeck.isFull() ? "Yes" : "No") << endl;
                        break;
                    }
                        case 11: {
                        cout << "\n=== Rules and Help ===" << endl;
                        Rules gameRules;
                        gameRules.browseRules();
                        break;
                    }   
                    case 12: {
                        cout << "\nThank you for using the Card Game System!" << endl;
                        break;
                    }
    
                    default: {
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                    }
                }
                
            } catch (const runtime_error& e) {
                cout << "Runtime Error: " << e.what() << endl;
                cout << "Please try again with valid input." << endl;
            } catch (const exception& e) {
                cout << "Exception: " << e.what() << endl;
            }
            
        } while (choice != 12);
        
    } catch (const runtime_error& e) {
        cout << "Fatal Runtime Error: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cout << "Fatal Exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "Unknown fatal error occurred." << endl;
        return 1;
    }
    
    return 0;
}

// Helper function implementations with robust input validation
int getValidInteger(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear remaining input
            if (value >= min && value <= max) {
                return value;
            } else {
                cout << "Value must be between " << min << " and " << max << ". ";
            }
        } else {
            cout << "Invalid input. Please enter a valid integer. ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string getValidString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        } else {
            cout << "Input cannot be empty. Please try again. ";
        }
    }
}

bool getValidBoolean(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value == 0 || value == 1) {
                return static_cast<bool>(value);
            } else {
                cout << "Please enter 1 for true or 0 for false. ";
            }
        } else {
            cout << "Invalid input. Please enter 1 or 0. ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double getValidDouble(const string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= min && value <= max) {
                return value;
            } else {
                cout << "Value must be between " << min << " and " << max << ". ";
            }
        } else {
            cout << "Invalid input. Please enter a valid number. ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}