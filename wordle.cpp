#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

// Helper function that will help cycle through the word to get all the info
void help_wordle( string current, int index, string floating,
    const set<string>& dict, set<string>& results );


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> result; // variable needed to get the final result back
    help_wordle(in, 0, floating, dict, result);
    return result;
}

// Define any helper functions here

// Helper function that will help cycle through the word to get all the info
void help_wordle( string current, int index, string floating,
    const set<string>& dict, set<string>& result )
{
  // Base case: Checking to see if the positions are all filled in place
  if(index == current.size()) {
    // Checking if all letters used and exist in dictionary 
    if(floating.empty() && dict.find(current) != dict.end()) {
      result.insert(current);
    }
      return; // end function
    
  }
  // Checking to see if the current character is fixed, if true move to the next character
  if(current[index] != '-') {
    help_wordle(current, index + 1, floating, dict, result);
  }
  else {
    // Checking for every lowercase letter in the current spot
    for(char c = 'a'; c <= 'z'; ++c) {
      current[index] = c;

      
      size_t pos = floating.find(c); // the letter is in the floating list is used here
      // Check if the current letter is in the list of floating letters.
      if(pos != string::npos) {
        // Use this floating letter and remove it from the list
        string newFloating = floating;
        newFloating.erase(pos, 1);
        help_wordle(current, index + 1, newFloating, dict, result);
      }
      else {
        // Only fill with a non-floating letter if there are enough remaining blanks
        // to still place all required floating letters
        if(count(current.begin(), current.end(), '-') >= floating.size()) {
          help_wordle(current, index + 1, floating, dict, result);
        }
      }
    }
  }
}
