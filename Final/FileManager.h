#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "Deck.h"

using namespace std;
namespace fs = std::filesystem;

class FileManager {
private:
    string saveDirectory;
    vector<string> deckFiles;
    
public:
    // Constructor
    FileManager(string directory = "./saves/");
    
    // Core functionality
    void listSavedDecks();
    string chooseDeckToLoad();
    bool loadSelectedDeck(Deck& deck);
    void saveNewDeck(const Deck& deck);
    void deleteSelectedDeck();
    
    // File operations
    void refreshFileList();
    bool createSaveDirectory();
    void displayDeckPreview(const string& filename);
    
    // Utility functions
    bool isValidDeckFile(const string& filename);
    string extractDeckName(const string& filename);
    void displayFileMenu();
    
    // Accessors
    vector<string> getAvailableDecks() const;
    string getSaveDirectory() const;
    void setSaveDirectory(const string& directory);
    
private:
    // Helper functions
    void displayHeader(const string& title) const;
    int getValidChoice(int min, int max);
    bool confirmAction(const string& action);
    string sanitizeFilename(const string& input);
};

#endif // FILEMANAGER_H