# Simple Spell Checker and Word Suggestion Program

This program implements a simple spell checker and word suggestion program using hashing. It reads a dictionary of words from a text file and provides the following functionalities:

1. **Case 1**: Checks if a word exists in the dictionary and suggests words starting with the same first two letters.
2. **Case 2**: If the input word does not exist in the dictionary due to a user misspelling, it suggests a recommended word from the dictionary based on the correct first letter.
3. **Case 3**: If the input word does not resemble any existing word in the dictionary, it returns "false".

## Files

- `main.cpp`: Contains the main code for the spell checker and word suggestion program.
- `Dictionary.txt`: A text file containing a list of words in the dictionary.
- `TimeInterval.h`: Header file for measuring execution time.

## How to Use

1. Compile the program using a C++ compiler.
2. Run the compiled executable.
3. Enter a word for spell checking when prompted.
4. The program will display whether the word is found in the dictionary and suggest similar words if applicable.
5. Execution time in microseconds will be displayed at the end of suggestions.

## Example

```
$ Please enter a word for spell checking:
$ hi
$ True
$ hic
$ him
$ hip
$ his
$ hit
$ 500 micro-sec.
```

## Dictionary

The dictionary used in this program contains a list of common words.

### Technologies Used

- **C++**: The primary programming language used for implementing the spell checker and word suggestion program. C++ offers features such as file I/O, string manipulation, and data structures, making it suitable for this project.
- **GNU Make**: Utilized for building and managing the project. Makefiles simplify the compilation process and help in organizing the project structure.
- **Data Structures**: Hash tables were used to efficiently store words from the dictionary, allowing for fast retrieval and spell checking.
- **Algorithms**: The program employs a hashing algorithm to generate hash codes for words, enabling quick lookup and comparison during spell checking and word suggestion.
- **Input/Output Handling**: Input from the user and reading from the dictionary file were managed using C++ standard input/output streams and file handling techniques.

### Concepts Implemented

- **Hashing**: The program utilizes hashing to map words to their corresponding hash codes, facilitating efficient storage and retrieval in the hash table.
- **Spell Checking**: By comparing the hash codes of user-input words with those stored in the hash table, the program determines whether a word exists in the dictionary.
- **Word Suggestion**: In cases where the input word is not found in the dictionary, the program suggests similar words based on the correct first letter of the word.
- **Execution Time Measurement**: The program includes functionality to measure the execution time of spell checking and word suggestion operations using the `TimeInterval` class and system time functions.

### Future Improvements

- **Improved Word Suggestions**: Enhance the word suggestion algorithm to provide more accurate and relevant suggestions based on similarity metrics such as edit distance.
- **User Interface**: Develop a graphical user interface (GUI) to improve user interaction and provide a more intuitive experience.
- **Expanded Dictionary**: Incorporate a larger and more comprehensive dictionary to increase the accuracy of spell checking and word suggestions.
- **Efficiency Enhancements**: Optimize the program for better performance, potentially by implementing more advanced data structures or algorithms for spell checking and suggestion.

## Note

- The program may suggest words based on the first two letters of the input word.