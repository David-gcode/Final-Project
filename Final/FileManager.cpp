#include "FileManager.h"
#include <iomanip>
#include <algorithm>
#include <limits>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime>

// Constructor implementation
FileManager::FileManager(string directory) : saveDirectory(directory) {
    createSaveDirectory();
    refreshFileList();
}

// Core functionality implementations
void FileManager::listSavedDecks() {
    refreshFileList();
    
    displayHeader("SAVED DECK FILES");
    
    if (deckFiles.empty()) {
        cout << "No saved deck files found in: " << saveDirectory << endl;
        cout << "Save a deck first to see it listed here." << endl;
        return;
    }
    
    cout << left << setw(5) << "No." << setw(25) << "Filename" 
         << setw(20) << "Deck Name" << "File Size" << endl;
    cout << string(70, '-') << endl;
    
    for (size_t i = 0; i < deckFiles.size(); i++) {
        string fullPath = saveDirectory + deckFiles[i];
        string deckName = extractDeckName(deckFiles[i]);
        
        // Get file size
        uintmax_t fileSize = 0;
        try {
            fileSize = fs::file_size(fullPath);
        } catch (const fs::filesystem_error&) {
            fileSize = 0;
        }
        
        cout << left << setw(5) << (i + 1) 
             << setw(25) << deckFiles[i]
             << setw(20) << deckName
             << fileSize << " bytes" << endl;
    }
    cout << endl;
}

string FileManager::chooseDeckToLoad() {
    refreshFileList();
    
    if (deckFiles.empty()) {
        cout << "No saved decks available to load." << endl;
        return "";
    }
    
    listSavedDecks();
    cout << "Enter the number of the deck to load (0 to cancel): ";
    
    int choice = getValidChoice(0, static_cast<int>(deckFiles.size()));
    
    if (choice == 0) {
        cout << "Load operation cancelled." << endl;
        return "";
    }
    
    string selectedFile = saveDirectory + deckFiles[choice - 1];
    cout << "Selected: " << deckFiles[choice - 1] << endl;
    
    // Show preview
    displayDeckPreview(selectedFile);
    
    if (confirmAction("load this deck")) {
        return selectedFile;
    }
    
    return "";
}

bool FileManager::loadSelectedDeck(Deck& deck) {
    string filename = chooseDeckToLoad();
    
    if (filename.empty()) {
        return false;
    }
    
    try {
        deck.loadFromBinary(filename);
        cout << "Deck loaded successfully from: " << filename << endl;
        return true;
    } catch (const runtime_error& e) {
        cout << "Error loading deck: " << e.what() << endl;
        return false;
    }
}

void FileManager::saveNewDeck(const Deck& deck) {
    displayHeader("SAVE DECK TO FILE");
    
    string baseName;
    cout << "Enter a name for your deck file (without extension): ";
    getline(cin, baseName);
    
    if (baseName.empty()) {
        baseName = deck.getDeckName();
    }
    
    // Sanitize filename
    string filename = sanitizeFilename(baseName) + ".dat";
    string fullPath = saveDirectory + filename;
    
    // Check if file exists
    if (fs::exists(fullPath)) {
        cout << "File '" << filename << "' already exists." << endl;
        if (!confirmAction("overwrite it")) {
            cout << "Save operation cancelled." << endl;
            return;
        }
    }
    
    try {
        // Open file in binary mode
        ofstream file(fullPath, ios::binary);
        if (!file) {
            throw runtime_error("Could not open file for writing: " + fullPath);
        }
        // Create a non-const reference to call saveToBinary
        const_cast<Deck&>(deck).saveToBinary(fullPath);
        cout << "Deck saved successfully as: " << filename << endl;
        refreshFileList();
    } catch (const runtime_error& e) {
        cout << "Error saving deck: " << e.what() << endl;
    }
}

void FileManager::deleteSelectedDeck() {
    refreshFileList();
    
    if (deckFiles.empty()) {
        cout << "No saved decks available to delete." << endl;
        return;
    }
    
    displayHeader("DELETE SAVED DECK");
    listSavedDecks();
    
    cout << "Enter the number of the deck to delete (0 to cancel): ";
    int choice = getValidChoice(0, static_cast<int>(deckFiles.size()));
    
    if (choice == 0) {
        cout << "Delete operation cancelled." << endl;
        return;
    }
    
    string selectedFile = deckFiles[choice - 1];
    string fullPath = saveDirectory + selectedFile;
    
    cout << "Selected for deletion: " << selectedFile << endl;
    displayDeckPreview(fullPath);
    
    if (confirmAction("permanently delete this deck file")) {
        try {
            fs::remove(fullPath);
            cout << "Deck file deleted successfully: " << selectedFile << endl;
            refreshFileList();
        } catch (const fs::filesystem_error& e) {
            cout << "Error deleting file: " << e.what() << endl;
        }
    } else {
        cout << "Delete operation cancelled." << endl;
    }
}

// File operations implementations
void FileManager::refreshFileList() {
    deckFiles.clear();
    
    try {
        if (fs::exists(saveDirectory) && fs::is_directory(saveDirectory)) {
            for (const auto& entry : fs::directory_iterator(saveDirectory)) {
                if (entry.is_regular_file()) {
                    string filename = entry.path().filename().string();
                    if (isValidDeckFile(filename)) {
                        deckFiles.push_back(filename);
                    }
                }
            }
        }
        
        // Sort files alphabetically
        sort(deckFiles.begin(), deckFiles.end());
        
    } catch (const fs::filesystem_error& e) {
        cout << "Error accessing save directory: " << e.what() << endl;
    }
}

bool FileManager::createSaveDirectory() {
    try {
        if (!fs::exists(saveDirectory)) {
            fs::create_directories(saveDirectory);
            cout << "Created save directory: " << saveDirectory << endl;
        }
        return true;
    } catch (const fs::filesystem_error& e) {
        cout << "Error creating save directory: " << e.what() << endl;
        return false;
    }
}

void FileManager::displayDeckPreview(const string& filename) {
    cout << "\n--- DECK PREVIEW ---" << endl;
    
    try {
        ifstream file(filename, ios::binary);
        if (!file) {
            cout << "Cannot read file for preview." << endl;
            return;
        }
        
        // Read deck name
        int nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        if (nameLength > 0 && nameLength < 1000) {  // Sanity check
            char* nameBuffer = new char[nameLength + 1];
            file.read(nameBuffer, nameLength);
            nameBuffer[nameLength] = '\0';
            cout << "Deck Name: " << string(nameBuffer) << endl;
            delete[] nameBuffer;
        }
        
        // Read owner name
        int ownerLength;
        file.read(reinterpret_cast<char*>(&ownerLength), sizeof(ownerLength));
        if (ownerLength > 0 && ownerLength < 1000) {  // Sanity check
            char* ownerBuffer = new char[ownerLength + 1];
            file.read(ownerBuffer, ownerLength);
            ownerBuffer[ownerLength] = '\0';
            cout << "Owner: " << string(ownerBuffer) << endl;
            delete[] ownerBuffer;
        }
        
        // Read max size and current size
        int maxSize, currentSize;
        file.read(reinterpret_cast<char*>(&maxSize), sizeof(maxSize));
        file.read(reinterpret_cast<char*>(&currentSize), sizeof(currentSize));
        
        cout << "Cards: " << currentSize << "/" << maxSize << endl;
        
        // Get file modification time
        auto ftime = fs::last_write_time(filename);
        auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
            ftime - fs::file_time_type::clock::now() + chrono::system_clock::now());
        auto cftime = chrono::system_clock::to_time_t(sctp);
        cout << "Last Modified: " << ctime(&cftime);
        
    } catch (const exception& e) {
        cout << "Error reading file preview: " << e.what() << endl;
    }
    
    cout << "-------------------\n" << endl;
}

// Utility function implementations
bool FileManager::isValidDeckFile(const string& filename) {
    // Check if file has .dat extension
    if (filename.length() < 4) return false;
    
    string extension = filename.substr(filename.length() - 4);
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    return extension == ".dat";
}

string FileManager::extractDeckName(const string& filename) {
    // Remove .dat extension and return as deck name
    if (filename.length() >= 4) {
        return filename.substr(0, filename.length() - 4);
    }
    return filename;
}

void FileManager::displayFileMenu() {
    displayHeader("FILE MANAGEMENT MENU");
    cout << "1. List All Saved Decks" << endl;
    cout << "2. Load Deck from File" << endl;
    cout << "3. Save Current Deck" << endl;
    cout << "4. Delete Saved Deck" << endl;
    cout << "5. Change Save Directory" << endl;
    cout << "6. Refresh File List" << endl;
    cout << "7. Return to Main Menu" << endl;
    cout << endl;
}

// Accessor implementations
vector<string> FileManager::getAvailableDecks() const {
    return deckFiles;
}

string FileManager::getSaveDirectory() const {
    return saveDirectory;
}

void FileManager::setSaveDirectory(const string& directory) {
    saveDirectory = directory;
    if (saveDirectory.back() != '/' && saveDirectory.back() != '\\') {
        saveDirectory += "/";
    }
    createSaveDirectory();
    refreshFileList();
}

// Private helper function implementations
void FileManager::displayHeader(const string& title) const {
    string border(title.length() + 4, '=');
    cout << "\n" << border << endl;
    cout << "  " << title << "  " << endl;
    cout << border << endl;
}

int FileManager::getValidChoice(int min, int max) {
    int choice;
    while (true) {
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice >= min && choice <= max) {
                return choice;
            } else {
                cout << "Please enter a number between " << min << " and " << max << ": ";
            }
        } else {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool FileManager::confirmAction(const string& action) {
    cout << "Are you sure you want to " << action << "? (y/n): ";
    char response;
    cin >> response;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return (response == 'y' || response == 'Y');
}

string FileManager::sanitizeFilename(const string& input) {
    string result = input;
    
    // Replace invalid characters with underscores
    string invalidChars = "<>:\"/\\|?*";
    for (char& c : result) {
        if (invalidChars.find(c) != string::npos) {
            c = '_';
        }
    }
    
    // Remove leading/trailing spaces
    result.erase(0, result.find_first_not_of(" \t"));
    result.erase(result.find_last_not_of(" \t") + 1);
    
    // Ensure it's not empty
    if (result.empty()) {
        result = "unnamed_deck";
    }
    
    return result;
}