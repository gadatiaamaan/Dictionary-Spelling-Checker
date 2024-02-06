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

## Note

- The program may suggest words based on the first two letters of the input word.
