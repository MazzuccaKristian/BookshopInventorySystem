#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::cin;
using std::string;

#define ARCHIVE "archive.txt"

void Setup();
int GetUserInput();
void ShowArchive();
bool SearchBook();
string ValidateString();
string StringFormatter(string* rawString);

/**
 * @brief Perform checks for archive.
 * 
 */
void Setup(){
    ifstream archive(ARCHIVE);
    if(archive.is_open()){
        // Archive file exists. Setup completed.
        archive.close();
    }else{
        // Archive file doesn't exist.
        ofstream newFile(ARCHIVE);
        if(newFile.is_open()){
            // Archive file created. Setup completed.
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
    cout << "3. Buy book;" << endl;
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

//TODO: search in file must be added. Must be done line-by-line?
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
        title = ValidateString();
        cout << "Enter author: ";
        author = ValidateString();
        cout << "TITOLO: " << title << ", AUTORE: " << author << endl;
    }
    return isFound;
}

/**
 * @brief Retrive raw input from user.
 * 
 * @return string Validated and formatted string.
 */
string ValidateString(){
    string rawInput, validatedString;
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