/*============================================================================
 |   Assignment:  pa01- Calculate the checksum of an input file given:
 |                 -> the name of the input file,
 |                 -> the checksum size of either 8, 16, or 32 bits
 |       Author:  Christopher Otto
 |     Language:  c++
 |   To Compile:  g++ -o pa01 pa01.cpp
 |   To Execute:  c++    -> ./pa01 inputFilename.txt checksumSize
 |                          where inputFilename.txt is the input file
 |                          and checksumSize is either 8, 16, or 32
 |         Note:
 |                All input files are simple 8 bit ASCII input
 |                All execute commands above have been tested on Eustis
 |        Class:  CIS3360 - Security in Computing - Spring 2025
 |   Instructor:  McAlpin
 |     Due Date:  6/22/2025
 +===========================================================================*/

// Preprocessor directives
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

// Prototypes
bool cmdLineArgumentValidation(int argc, char ** argv, std::ifstream &inputFile);
int echoInput(char ** argv, std::ifstream &inputFile);
void calculateChecksum(char ** argv, std::ifstream &inputFile, int characterCnt);

int main(int argc, char ** argv)
{
    // #file chars + #req. padding
    int characterCnt; 

    std::ifstream inputFile(argv[1]);

    // Verify input is valid and stop program if false
    if(cmdLineArgumentValidation(argc, argv, inputFile) != true)
    {
        inputFile.close();
        return 1;
    }

    // Echo the input in the input file
    characterCnt = echoInput(argv, inputFile);

    // Calculate checksum
    calculateChecksum(argv, inputFile, characterCnt);

    // Close inputFile
    inputFile.close();

    return 0;
}

// Verify input is valid and return true for yes and false for no
bool cmdLineArgumentValidation(int argc, char ** argv, std::ifstream &inputFile)
{
    if(argc != 3)
    {
        std::cerr << "Incorrect number of arguments. './pa01 [inputFilename.txt] [checksumSize]' to execute." << std::endl;
        return false;
    }

    if(argv[2] != std::string("8") && argv[2] != std::string("16") && argv[2] != std::string("32"))
    {
        std::cerr << "Valid checksum sizes are 8, 16, or 32" << std::endl;
        return false;
    }

    if(!inputFile.is_open())
    {
        std::cerr << "Input file could not be opened." << std::endl;
        return false;
    }

    return true;
}

// Echo the input to the console, returning total chars including padding
int echoInput(char ** argv, std::ifstream &inputFile)
{
    int charsPrinted = 0;
    int charsOnLine = 0;
    int paddingNeeded;
    char curChar;

    // Input already validated, so just assign size to checkSumSize
    int checkSumSize = std::stoi(std::string(argv[2]));

    std::cout << std::endl; // Req. for formatting    

    // Loop through all characters in order to print them to the console
    while(inputFile.get(curChar))
    {
        // Print characters to console
        std::cout << curChar;

        // Increment counters
        charsOnLine++;
        charsPrinted++;

        // Only 80 characters per line
        if(charsOnLine == 80)
        {
            std::cout << std::endl;
            charsOnLine = 0; // Reset line counter
        }
    }

    // Calculate padding needed
    if((charsPrinted * 8) % checkSumSize == 0) // No padding needed
    {
        paddingNeeded = 0;
    }
    else // Calculate padding
    {
        paddingNeeded = (checkSumSize - ((charsPrinted * 8) % checkSumSize)) / 8;
    }

    // Print needed padding if there is any
    for(int paddingPrinted = 0; paddingPrinted < paddingNeeded; ++paddingPrinted)
    {
        std::cout << 'X';
    }

    // Move to next line if neccesary
    if(charsOnLine != 0) std::cout << std::endl;

    // Reset position of ifstream to beginning
    inputFile.clear();
    inputFile.seekg(0);

    // Return total chars, including padding
    return charsPrinted + paddingNeeded;
}

// Calculate and print the checksum value for the message
void calculateChecksum(char ** argv, std::ifstream &inputFile, int characterCnt)
{
    uint64_t checksum = 0; // Final checksum value
    uint64_t nextWord = 0;
    bool reachedEOF = false;
    char curChar;

    // Input already validated, so just assign size to checkSumSize
    int checkSumSize = std::stoi(std::string(argv[2]));

    // All potentially needed bit masks
    uint64_t bitMask8 = 0xFF;
    uint64_t bitMask16 = 0xFFFF;
    uint64_t bitMask32 = 0xFFFFFFFF;

    // Calculate checksum by looping over all characters and building words as we go
    for(int curCharPos = 1; curCharPos <= characterCnt; ++curCharPos)
    {
        // Get next character from file and flag if EOF is reached
        if(reachedEOF == false && !inputFile.get(curChar))
        {
            reachedEOF = true;
        }

        // Set curChar to pad value ('X') if we've reached EOF
        if(reachedEOF == true)
        {
            curChar = 'X';
        }

        // Shift curChar by appropriate amount to build nextWord
        if((curCharPos * 8) % checkSumSize == 0) // No shift necessarry
        {
            nextWord += curChar;
        }   
        else if((curCharPos * 8) > checkSumSize)
        {
            nextWord += curChar << ((curCharPos * 8) % checkSumSize);
        }
        else
        {
            nextWord += curChar << (checkSumSize - (curCharPos * 8));
        }

        // If word is built, add to checksum, ignoring overflow, and reset word
        if((curCharPos * 8) % checkSumSize == 0)
        {
            // Add word to checksum
            checksum += nextWord;

            // Wipe any overflow to ensure impossibility of wrapping errors
            switch(checkSumSize)
            {
                case 8:
                    checksum &= bitMask8;
                    break;
                case 16:
                    checksum &= bitMask16;
                    break;
                case 32:
                    checksum &= bitMask32;
                    break;
            }

            nextWord = 0; // Reset word
        }
    }

    // Print output message with checkSumSize, checkSum in hex, and characterCnt
    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, ((long unsigned int) checksum), characterCnt);
}

/*=============================================================================
 |     I Christopher Otto (ch503042) affirm that this program is
 | entirely my own work and that I have neither developed my code together with
 | any another person, nor copied any code from any other person, nor permitted
 | my code to be copied or otherwise used by any other person, nor have I
 | copied, modified, or otherwise used programs created by others. I acknowledge
 | that any violation of the above terms will be treated as academic dishonesty.
 +=============================================================================*/