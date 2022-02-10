#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::istringstream;

#define ARCHIVE "archive.txt"
#define TEMP "archive_temp.txt"

void Setup();
int GetUserInput();
void ShowArchive();
bool SearchBook();
string GetValidString();
string StringFormatter(string* rawString);
void RentBook();

/**
 * @brief Perform checks for archive.
 * 
 */
void Setup(){
    ifstream archive(ARCHIVE);
    if(archive.is_open()){
        // Archive exists. Setup completed.
        archive.close();
    }else{
        // Archive doesn't exist.
        ofstream newFile(ARCHIVE);
        if(newFile.is_open()){
            // Archive created. Setup completed.
            newFile.close();
        }
    }
}

/**
 * @brief Show app's main menu (inline).
 * 
 */
void inline ShowMainMenu(){
    cout << "--MAIN MENU--" << endl;
    cout << "1. Show archive;" << endl;
    cout << "2. Search book;" << endl;
    cout << "3. Rent book;" << endl;
    cout << "0. Exit." << endl;
}

/**
 * @brief Retrive user's choice (for main menu).
 * 
 * @return int Validated choice.
 */
int GetUserChoice(){
    int choice;
    bool isValid = false;
    do{
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice >= 0 && choice <= 3){
            isValid = true;
        }else{
            cout << "Choice not allowed. Please, try again..." << endl;
        }
    }while(!isValid);
    cin.ignore();
    return choice;
}

/**
 * @brief Display content of archive.
 * 
 */
void ShowArchive(){
    ifstream archive(ARCHIVE);
    string line;
    if(archive.is_open()){
        while(getline(archive, line)){
            cout << line << endl;
        }
    }else{
        perror("ARCHIVE");
    }
}

/**
 * @brief From user's input (title and author), search for a specific book in archive.
 * 
 * @return true If the book exists in archive.
 * @return false 
 */
bool SearchBook(){
    bool isFound = false;
    string title, author;
    ifstream archive(ARCHIVE);
    if(!archive.is_open()){
        perror("ARCHIVE");
    }else{
        cout << "Enter title: ";
        title = GetValidString();
        cout << "Enter author: ";
        author = GetValidString();
        string line;
        while(getline(archive, line)){
            istringstream stringStream(line);
            string key, value;
            bool isTitleFound = false;
            bool isAuthorFound = false;
            while(stringStream >> key >> value){ // Key-value pair from archive
                if((key.compare("Title:") == 0) && (value.compare(title) == 0)){
                    // Title is correct.
                    isTitleFound = true;
                }else if((key.compare("Author:") == 0) && (value.compare(author) == 0)){
                    // Author is correct
                    isAuthorFound = true;
                }
            }
            if(isTitleFound && isAuthorFound){
                isFound = true;
            }
            stringStream.clear(); // Reset istringstream for next line
        }
        archive.close();
    }
    return isFound;
}

/**
 * @brief Retrive raw input from user.
 * 
 * @return string Validated and formatted string.
 */
string GetValidString(){
    string rawInput;
    getline(cin, rawInput);
    return StringFormatter(&rawInput);
}

/**
 * @brief Format an input: replace a whitespace with an underscore.
 * NOTE: Must be used for interactions with the archive.
 * 
 * @param rawString raw input pointer.
 * @return string Formatted string.
 */
string StringFormatter(string* rawString){
    string newString = *(rawString);
    while(newString.find_first_of(' ') != newString.npos){
        newString.replace(newString.find_first_of(' '), 1, "_");
    }
    return newString;
}

void RentBook(){
    string title, author;
    ifstream archive(ARCHIVE);
    ofstream newArchive(TEMP);
    if(archive.is_open() && newArchive.is_open()){
        cout << "Enter title: ";
        title = GetValidString();
        cout << "Enter author: ";
        author = GetValidString();
        string line;
        while(getline(archive, line)){
            string newRecord;
            istringstream stringStream(line);
            string key, value;
            bool isTitleFound = false;
            bool isAuthorFound = false;
            bool isAvailable = false;
            int copies = 0;
            while(stringStream >> key >> value){ // Key-value pair from archive
                if((key.compare("Title:") == 0) && (value.compare(title) == 0)){
                    // Title is correct.
                    isTitleFound = true;
                }else if((key.compare("Author:") == 0) && (value.compare(author) == 0)){
                    // Author is correct
                    isAuthorFound = true;
                }else if(key.compare("Copies:") == 0){
                    copies = std::stoi(value);
                    if(copies > 0){
                        isAvailable = true;
                        copies--;
                    }
                }
            }
            if(isTitleFound && isAuthorFound && isAvailable){
                newRecord = "Title: " + title + " Author: " + author + " Copies: " + std::to_string(copies);
            }else{
                newRecord = line;
            }
            newArchive << newRecord << endl;
            stringStream.clear(); // Reset istringstream for next line
        }
        archive.close();
        newArchive.close();
        remove(ARCHIVE);
        rename(TEMP, ARCHIVE);
    }else{
        perror("Archive.txt");
    }
}
    

