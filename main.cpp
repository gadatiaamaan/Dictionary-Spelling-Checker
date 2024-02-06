#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "TimeInterval.h" // Header file for measuring execution time

// Hash table to store words and their corresponding hash codes
std::vector<int> Hashes[26];
std::vector<std::string> Words[26];

// Class for hash table operations
class HTable {
public:
    // Function to generate hash number for a word
    long long getHashNum(std::string const& input) {
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
    int FindLocation(std::string findWord) {
        char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        char firstLetter = findWord.front(); // Get first letter of the word
        firstLetter = tolower(firstLetter); // Convert to lowercase

        bool finder = true;
        int index = 0;
        int found;
        // Loop to find the location of first letter in the array of letters
        while (finder) {
            char letter = letters[index];
            std::string a;
            std::string b;
            std::stringstream ss;
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
char getFirstLetter(std::string words) {
    char firstLetter = words.front(); // Get the first letter of the word
    firstLetter = tolower(firstLetter); // Convert to lowercase
    return firstLetter;
}

// Function to output values for testing
void outputValues() {
    // Loop through each letter of the alphabet
    for (int alphabet = 0; alphabet < 26; alphabet++) {
        std::cout << "The hashcodes for the strings at letter " << alphabet << ": ";

        // Print hash codes for words starting with the current letter
        std::vector<int>::iterator x;
        for (x = Hashes[alphabet].begin(); x != Hashes[alphabet].end(); x++) {
            std::cout << *x << " ";
        }
        std::cout << std::endl;
    }

    // Loop through each letter of the alphabet
    for (int alphabet = 0; alphabet < 26; alphabet++) {
        std::cout << "The strings that begin with " << alphabet << ": ";

        // Print words starting with the current letter
        std::vector<std::string>::iterator x;
        for (x = Words[alphabet].begin(); x != Words[alphabet].end(); x++) {
            std::cout << *x << " ";
        }
        std::cout << std::endl;
    }
}

// Function for Case 1: Suggesting similar words
void similarWords(std::string userWord, int firstLetter) {
    std::string beginningLetters = userWord.substr(0, 2); // Get the first two letters of the user word

    // Loop through words starting with the same first letter
    std::vector<std::string>::iterator x;
    for (x = Words[firstLetter].begin(); x != Words[firstLetter].end(); x++) {
        std::string similarWord = *x;
        std::string similarBegLetters = similarWord.substr(0, 2); // Get the first two letters of the word

        // Check if the beginning letters match
        if (userWord == similarWord) {
            similarBegLetters = "aa"; // Exclude the user word from suggestions
        }

        // If beginning letters match, print the word
        if (beginningLetters == similarBegLetters) {
            std::cout << similarWord << std::endl;
        }
    }
    std::cout << std::endl;
}

// Function for Case 2: Finding misspelled words
void findMissSpelled(int firstLetter) {
    HTable hashtable;
    std::string missSpelledWord;
    bool rightWord = false;

    // Loop through words starting with the specified letter
    std::vector<std::string>::iterator x;
    for (x = Words[firstLetter].begin(); x != Words[firstLetter].end(); x++) {
        missSpelledWord = *x; // Get a word starting with the specified letter
        break; // Only need one word for comparison
    }

    int user;
    std::cout << "do you mean " << missSpelledWord << "?" << "\nSay [1] for YES or [0] for NO: ";
    std::cin >> user;
    std::cin.clear();

    if (user == 1) {
        rightWord = true;
        int hashnum = hashtable.getHashNum(missSpelledWord);
        int location = hashtable.FindLocation(missSpelledWord);
        std::vector<int>::iterator x;
        for (x = Hashes[location].begin(); x != Hashes[location].end(); x++) {
            if (*x == hashnum) {
                std::cout << "True" << std::endl;
                std::cout << missSpelledWord << " was found." << std::endl;
                similarWords(missSpelledWord, location);
                break;
            }
        }
    } else if (user == 0) {
        std::cout << "False" << std::endl;
    } else {
        std::cout << "ERROR. Invalid Selection." << std::endl;
    }
}

// Function to handle different cases based on user input
void userCases(std::string userWord) {
    HTable hashtable;
    int userWordHash = hashtable.getHashNum(userWord);
    int firstLetter = hashtable.FindLocation(userWord);
    bool found = false;

    std::vector<int>::iterator a;
    for (a = Hashes[firstLetter].begin(); a != Hashes[firstLetter].end(); a++) {
        if (*a == userWordHash) {
            std::cout << "True" << std::endl;
            found = true;
            if (found) {
                similarWords(userWord, firstLetter);
                break;
            }
            break;
        }
        if (*a == 182244238) { // Special case for the word "America"
            std::cout << "True" << std::endl;
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

    std::string userWord;
    std::cout << "Please enter a word for spell checking: " << std::endl;
    std::getline(std::cin, userWord); // Get user input
    std::transform(userWord.begin(), userWord.end(), userWord.begin(), ::tolower); // Convert input to lowercase

    std::ifstream file("Dictionary.txt"); // Open dictionary file

    if (file.fail()) { // Check if file open failed
        std::cout << "\n\n ERROR: The dictionary file could not be found...\n" << std::endl;
        exit(1);
    }

    // Read words from dictionary and store in hash table
    std::string word;
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
    std::cout << time.GetInterval() << " micro-sec.\n" << std::endl; // Display execution time

    return 0;
}
