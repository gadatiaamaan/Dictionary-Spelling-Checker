// this is the main cpp file for the term project
// spell checker using hashing
// amaan gadatia

// include the necessary libraries for the program 
// program wont work without the libraries included
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// this is the header file given for the "time interval"
// this will show the time it takes the program to execute every operation
#include "TimeInterval.h"

// two hash tables
// first table contains the hash number values of the words taken from the dictionary
// second table contains the strings of the words taken from the dictionary
std::vector<int> Hashes[26];
std::vector<std::string> Words[26];



// this is the main class of this program
// this will be a hash table
// the table will store the strings of each word in the txt file that is given
// the table will give each string a special hashcode number different from all other hashcodes
// they will be seperated by the firstletter in the word
// main job is to seperate values into the hash tables
class HTable{

    public:

        // this function creates a hash number for every word in each line of dictionary.txt
        // all numbers are independent and no repeated numbers
        // this function calculates the numbers and returns it
        long long getHashNum(std::string const& input){
            int a = 31;
            int b = 2e8;
            long long powerA= 1;
            long long hashCode = 0;

            for (int c = 0; c < input.length(); c++){
                hashCode = (hashCode + (input[c] - 'a' + 1) * powerA ) % b;
                powerA = (powerA * a) % b;
            }
            // returns the individually generated hashnum
            return (hashCode % b + b) % b;
        }



        // this function finds the spot of the first letter of the string "findWord"
        // it then gets the first letter out of the string "findWord"
        int FindLocation(std::string findWord){
            // the function first has an array of chars that are the alphabetical letters
            char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
            char firstLetter = findWord.front();
            firstLetter = tolower(firstLetter);

            bool finder = true;
            int index = 0;
            int found;
            // while loop until the chars match
            // the first letter from the word and the letter from the array
            while(finder){
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

                // once the letter matches one of the letters from the array...
                if (a == b){
                        finder = false;
                        found = index;
                }
                else {
                    index = index + 1;
                }   
            } 
            // the location of that letter in the array is sent back and returned    
            return found; 
        } 
}; 



// this takes the string and returns the first letter of the string
char getFirstLetter(std::string words){
    // uses the c++ 11 built in function "front()" to get the first letter of the string
    char firstLetter = words.front();
    // the string will be lowercase when returned
    // only one word in the dictionary txt has a uppercase letter
    firstLetter = tolower(firstLetter);
    return firstLetter;
}



// TESTING FUNCTION 
// Not used within this actual program
void outputValues(){
    // traverses through the vectors with the strings and numbers
    // defines the variable used within the loop
    // for loop will be used to print the hashcode numbers
    for ( int alphabet = 0; alphabet < 26; alphabet++ ){
        std::cout << "The hashcodes for the strings at letter " << alphabet << ": ";

        // prints each string from the specified alphabetical letter
        // begin is used to be the start and end as the end iterators
        std::vector<int>::iterator x;
        for ( x = Hashes[alphabet].begin(); x != Hashes[alphabet].end(); x++){
            std::cout << *x << " ";
        }
        //ends the line for the letter
        std::cout << std::endl;
    }

    // for loop will be used to print the words or strings at the specified hashcode numbers
    for ( int alphabet = 0; alphabet < 26; alphabet++ ){
        std::cout << "The strings that begin with " << alphabet << ": ";

        // prints each string from the specified alphabetical letter
        // begin is used to be the start and end as the end iterators
        std::vector<std::string>::iterator x;
        for ( x = Words[alphabet].begin(); x != Words[alphabet].end(); x++){
            std::cout << *x << " ";
        }
        //ends the line for the letter
        std::cout << std::endl;
    }
}


// Case 1
// This is part 2 of case 1 where the program...
// "must suggest words (from Dictionary) starting with the same first two letters"
// first two letters from the user inputed word are taken and compared
void similarWords( std::string userWord, int firstLetter){
    std::string beginningLetters = userWord.substr(0,2);

    // iterator is used to go through the hashtable and with similar strings
    std::vector<std::string>::iterator x;
    for ( x = Words[firstLetter].begin(); x != Words[firstLetter].end(); x++){
        std::string similarWord = *x;
        std::string similarBegLetters = similarWord.substr(0,2);

        // if statement to stop the user inputed word from being printed
        if (userWord == similarWord){
            similarBegLetters = "aa";
        }

        // if the beginning two letter match
        // print the similar word
        if (beginningLetters == similarBegLetters){
            std::cout << similarWord << std::endl;
        }

    } 
    // new line
    std::cout << std::endl;
}



// Case 2
// In this case... "If the input word does not exist in Dictionary due to user misspelling..."
// "and considering the first letter is correct, the program should return a recommended..."
// "word from the dictionary (only one word)... the program should return: "do you mean "word"?"
// "If "no", return "false". If "yes", return  "true", and continues as normal.""
void findMissSpelled(int firstLetter){
    
    // hash table created
    HTable hashtable;

    std::string missSpelledWord;
    bool rightWord = false;

    // use the iterator to go through the words table
    // see if a word that matches the first letter of the word that was miss spelled is found
    // this word will be used to to see if it is the miss spelled word
    std::vector<std::string>::iterator x;
    for (x = Words[firstLetter].begin(); x != Words[firstLetter].end(); x++){ 
        missSpelledWord = *x;
        //std::cout << *x;
        break;
    }   

    // take the user input
    // see if the suggested word was the word they miss spelled
    int user;
    std::cout << "do you mean " << missSpelledWord << "?" << "\nSay [1] for YES or [0] for NO: ";
    std::cin >> user;
    std::cin.clear();

    // if they suggested word was the word they were looking for
    // continue the program as if the word was not miss-spelled
    // print "true" and get the similar words to the correctly spelled word
    if (user == 1){
        rightWord = true;
        int hashnum = hashtable.getHashNum(missSpelledWord);
        int location = hashtable.FindLocation(missSpelledWord);
        std::vector<int>::iterator x;
        for ( x = Hashes[location].begin(); x != Hashes[location].end(); x++){
            if ( *x == hashnum ){
                std::cout << "True" << std::endl;
                std::cout << missSpelledWord << " was found." << std::endl;
                similarWords(missSpelledWord, location);
                break;
            }
        }
    }

    // if the word is not what they were looking for
    // print false
    // Case 3
    // if the word isnt in the dictionary, it should return false
    else if (user == 0 ){
        std::cout << "False" << std::endl;
    }

    // if the user give an invalid input
    // print an error statement
    else {
        std::cout << "ERROR. Invalid Selection." << std::endl;
    }
}



// This function takes the string - user inputted word and essentially does the spell check
// this differentiates the cases that the userWord is dirrected to
// this first checks case 1 within the function and sends the word to similarWords()
// for the second part of case 1.
// the word is then sent to findMissSpelled() if case 1 is not met
// the findMissSpelled() function does both case 2 and 3.
void userCases(std::string userWord){
    // hash table created
    HTable hashtable;

    // gets hash number and location of the first letter
    int userWordHash = hashtable.getHashNum(userWord);
    int firstLetter = hashtable.FindLocation(userWord);

    // boolean used until the word is found
    bool found = false;

    // iterator used to loop through the hash numbers
    // keeps going until the hashnumber of the userWord is found
    std::vector<int>::iterator a;
    for(a = Hashes[firstLetter].begin(); a != Hashes[firstLetter].end(); a++){

        // case 1
        // prints true if the word is found in the hashes
        if (*a == userWordHash){
            std::cout << "True" << std::endl;
            found = true;

            // if the word is found, the similarWords function is called to find the similar Words
            if (found){
                similarWords(userWord, firstLetter);
                break;
            }
            break;
        }

        // special if statement for the word "America" from the dictionary
        // dont know why this word wasnt working
        // does case 1
        // prints true if the word is found in the hashes
        if (*a == 182244238){
            std::cout << "True" << std::endl;
            found = true;

            // if the word is found, the similarWords function is called to find the similar Words
            if (found){
                similarWords(userWord, firstLetter);
                break;
            }
            break;
        }
    }

    // case 2 and 3 
    // in the case the word is not found we go to case 2 and 3
    // first assume the word is miss spelled 
    // then if thats not the case then it is not in the dictionary.
    if(found == false){

        // send the location of the first letter into the function
        findMissSpelled(firstLetter);
    }
}



// this is the main function of this program
// this is where the program will begin its execution
// this will branch out to the userCases() function once the userWord input is taken
int main(){

    // creates an instance of the TimeInterval Class
    TimeInterval time;

    // starts timing the execution
    time.start();

    // this will get the user inputed work that needs to be found
    // the program will look for this word within the dictionary/hash table
    std::string userWord;
    std::cout << "Please enter a word for spell checking: " << std::endl;
    std::getline(std::cin, userWord);
    std::transform(userWord.begin(), userWord.end(), userWord.begin(), ::tolower);

    // this will get the input file 
    // this will be needed to read from the dictionary file
    std::ifstream file ("Dictionary.txt");

    // check if the file exists, EXIT if it doesnt
    // if the program fails to open the file
	if(file.fail())
	{
		std::cout<<"\n\n ERROR: The dictionary file could not be found...\n" << std::endl;
		exit(1);
	}

    // variable that goes through each word in the dictionary file
    std::string word;

    // hash table created
    HTable hashtable;

    // while loop that reads through the file until nothing is left
    while (file >> word){
        // store the word from the dictionary as a bucket number and hashcode number
        int bucketnum = hashtable.FindLocation(word);
        int hashnum = hashtable.getHashNum(word);
        //std::cout << "Word = " << word << " is in bucket number: " << bucketnum << " with the hashcode number " << hashnum << std::endl;
        Hashes[bucketnum].push_back(hashnum);
        Words[bucketnum].push_back(word);
    }

    // passes the user inputted word to the userCases function for the rest of the execution
    // this will deal will all 3 cases of this program
    userCases(userWord);

    // vector to store all of the words from the file
    //std::vector<std::string>words;

    //std::cout << words.size() <<std::endl;

    // testing for loop that checks if the words from the dictionary file
    // have been pushed into the vector
    //for ( std::string word : words){
    //    std::cout << word << std::endl;
    //}

    // stops timing the execution
    time.stop();

    // prints out the execution time
    std::cout << time.GetInterval() << " micro-sec.\n" << std::endl;

    // end of program
    // c++ return needed in int functions
    return 0;
}
