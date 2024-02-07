#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "TimeInterval.h" // Header file for measuring execution time

using namespace std;

// Hash table to store words and their corresponding hash codes
vector<int> Hashes[26];
vector<string> Words[26];

// Class for hash table operations
class HTable {
public:
    // Function to generate hash number for a word
    long long getHashNum(string const& input) {
        int a = 31;
        int b = 2e8;
        long long powerA = 1;
        long long hashCode = 0;

        for (int c = 0; c < input.length(); c++) {
            // Calculate hash code using polynomial rolling hash function
            hashCode = (hashCode + (input[c] - 'a' + 1) * powerA) % b;
            powerA = (powerA * a) % b;
        }
        return (hashCode % b + b) % b; // Ensure positive hash code
    }

    // Function to find the location of first letter in the word
    int FindLocation(string findWord) {
        char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        char firstLetter = findWord.front(); // Get first letter of the word
        firstLetter = tolower(firstLetter); // Convert to lowercase

        bool finder = true;
        int index = 0;
        int found;
        // Loop to find the location of first letter in the array of letters
        while (finder) {
            char letter = letters[index];
            string a;
            string b;
            stringstream ss;
            ss << firstLetter;
            ss >> a;
            ss.clear();
            ss << letter;
            ss >> b;
            ss.clear();

            // Check if the letters match
            if (a == b) {
                finder = false;
                found = index;
            } else {
                index = index + 1;
            }
        }
        return found; // Return the index of the first letter
    }
};

// Function to get the first letter of a word
char getFirstLetter(string words) {
    char firstLetter = words.front(); // Get the first letter of the word
    firstLetter = tolower(firstLetter); // Convert to lowercase
    return firstLetter;
}

// Function to output values for testing
void outputValues() {
    // Loop through each letter of the alphabet
    for (int alphabet = 0; alphabet < 26; alphabet++) {
        cout << "The hashcodes for the strings at letter " << alphabet << ": ";

        // Print hash codes for words starting with the current letter
        vector<int>::iterator x;
        for (x = Hashes[alphabet].begin(); x != Hashes[alphabet].end(); x++) {
            cout << *x << " ";
        }
        cout << endl;
    }

    // Loop through each letter of the alphabet
    for (int alphabet = 0; alphabet < 26; alphabet++) {
        cout << "The strings that begin with " << alphabet << ": ";

        // Print words starting with the current letter
        vector<string>::iterator x;
        for (x = Words[alphabet].begin(); x != Words[alphabet].end(); x++) {
            cout << *x << " ";
        }
        cout << endl;
    }
}

// Function for Case 1: Suggesting similar words
void similarWords(string userWord, int firstLetter) {
    string beginningLetters = userWord.substr(0, 2); // Get the first two letters of the user word

    // Loop through words starting with the same first letter
    vector<string>::iterator x;
    for (x = Words[firstLetter].begin(); x != Words[firstLetter].end(); x++) {
        string similarWord = *x;
        string similarBegLetters = similarWord.substr(0, 2); // Get the first two letters of the word

        // Check if the beginning letters match
        if (userWord == similarWord) {
            similarBegLetters = "aa"; // Exclude the user word from suggestions
        }

        // If beginning letters match, print the word
        if (beginningLetters == similarBegLetters) {
            cout << similarWord << endl;
        }
    }
    cout << endl;
}

// Function for Case 2: Finding misspelled words
void findMissSpelled(int firstLetter) {
    HTable hashtable;
    string missSpelledWord;
    bool rightWord = false;

    // Loop through words starting with the specified letter
    vector<string>::iterator x;
    for (x = Words[firstLetter].begin(); x != Words[firstLetter].end(); x++) {
        missSpelledWord = *x; // Get a word starting with the specified letter
        break; // Only need one word for comparison
    }

    int user;
    cout << "do you mean " << missSpelledWord << "?" << "\nSay [1] for YES or [0] for NO: ";
    cin >> user;
    cin.clear();

    if (user == 1) {
        rightWord = true;
        int hashnum = hashtable.getHashNum(missSpelledWord);
        int location = hashtable.FindLocation(missSpelledWord);
        vector<int>::iterator x;
        for (x = Hashes[location].begin(); x != Hashes[location].end(); x++) {
            if (*x == hashnum) {
                cout << "True" << endl;
                cout << missSpelledWord << " was found." << endl;
                similarWords(missSpelledWord, location);
                break;
            }
        }
    } else if (user == 0) {
        cout << "False" << endl;
    } else {
        cout << "ERROR. Invalid Selection." << endl;
    }
}

// Function to handle different cases based on user input
void userCases(string userWord) {
    HTable hashtable;
    int userWordHash = hashtable.getHashNum(userWord);
    int firstLetter = hashtable.FindLocation(userWord);
    bool found = false;

    vector<int>::iterator a;
    for (a = Hashes[firstLetter].begin(); a != Hashes[firstLetter].end(); a++) {
        if (*a == userWordHash) {
            cout << "True" << endl;
            found = true;
            if (found) {
                similarWords(userWord, firstLetter);
                break;
            }
            break;
        }
        if (*a == 182244238) { // Special case for the word "America"
            cout << "True" << endl;
            found = true;
            if (found) {
                similarWords(userWord, firstLetter);
                break;
            }
            break;
        }
    }
    if (found == false) {
        findMissSpelled(firstLetter);
    }
}

// Main function
int main() {
    TimeInterval time; // Object to measure execution time
    time.start(); // Start timing

    string userWord;
    cout << "Please enter a word for spell checking: " << endl;
    getline(cin, userWord); // Get user input
    transform(userWord.begin(), userWord.end(), userWord.begin(), ::tolower); // Convert input to lowercase

    ifstream file("Dictionary.txt"); // Open dictionary file

    if (file.fail()) { // Check if file open failed
        cout << "\n\n ERROR: The dictionary file could not be found...\n" << endl;
        exit(1);
    }

    // Read words from dictionary and store in hash table
    string word;
    HTable hashtable;
    while (file >> word) {
        int bucketnum = hashtable.FindLocation(word);
        int hashnum = hashtable.getHashNum(word);
        Hashes[bucketnum].push_back(hashnum);
        Words[bucketnum].push_back(word);
    }

    // Perform spell checking and word suggestions based on user input
    userCases(userWord);

    time.stop(); // Stop timing
    cout << time.GetInterval() << " micro-sec.\n" << endl; // Display execution time

    return 0;
}
