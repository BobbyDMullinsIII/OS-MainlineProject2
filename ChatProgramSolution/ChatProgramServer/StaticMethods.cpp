#include <iostream>
#include <fstream>
#include <string>
#include "StaticMethods.h"
using namespace std;

//Constructor
StaticMethods::StaticMethods() {}

//Deconstructor
StaticMethods::~StaticMethods() {}


//Method for checking if number is a power of two
//Stolen from https://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2
//Returns if the input number (x) is a power of 2 (And not 0)
bool StaticMethods::IsPowerOfTwo(int x)
{
    return (x != 0) && ((x & (x - 1)) == 0);

}//end IsPowerOfTwo()

//Method for removing all characters that are not letters from string
//Stolen from https://www.geeksforgeeks.org/remove-characters-alphabets-string/
//Returns string with only letter (A-Z,a-z) characters 
string StaticMethods::removeNonLetters(string s)
{
    //For every character in string, delete all non-letter (A-Z,a-z) characters
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] < 'A' || s[i] > 'Z' && s[i] < 'a' || s[i] > 'z')
        {
            s.erase(i, 1);
            i--;
        }
    }

    return s;
}