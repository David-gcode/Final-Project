#ifndef RULES_H
#define RULES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rules {
private:
    vector<string> gameRules;
    vector<string> cardTypes;
    vector<string> deckOperations;
    
public:
    // Constructor
    Rules();
    
    // Rule display functions
    void displayAllRules() const;
    void displayCardRules() const;
    void displayDeckRules() const;
    void displayGameplayRules() const;
    void displayMenuHelp() const;
    
    // Interactive rule browsing
    void browseRules() const;
    
    // Rule search functionality
    void searchRules(const string& keyword) const;
    
private:
    // Helper functions to initialize rule sets
    void initializeGameRules();
    void initializeCardTypes();
    void initializeDeckOperations();
    
    // Utility functions
    void displaySection(const string& title, const vector<string>& content) const;
    void displayHeader(const string& title) const;
};

#endif // RULES_H