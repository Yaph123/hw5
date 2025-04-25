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


void allCombos(
    std::string current,
    int index,
    std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& table)
{

    if(index == current.size()){
        if(floating.empty() && dict.find(current) != dict.end()){
            table.insert(current);
        }
     return;
    }
    
    if(current[index] != '-'){
        allCombos(current, index + 1, floating, dict, table);
        return;
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        bool floatUsed= false;
        std::string newFloating = floating;

        // If c is a floating letter, use it
        for (size_t i = 0; i < floating.size(); ++i) {
            if (floating[i] == c) {
                newFloating.erase(i, 1);
                floatUsed = true;
                break;
            }
        }

        int remainingSlots = 0;
        for(size_t j = index; j < current.size(); ++j){
            if(current[j] == '-'){
                ++remainingSlots;
            } 
        }
            if(!floatUsed && remainingSlots <= newFloating.size()){
                continue;
        }

        current[index] = c;
        allCombos(current, index + 1, newFloating, dict, table);
        current[index] = '-';
    }
}


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<string> table;
    allCombos(in,0,floating,dict,table);
    return table;
}

// Define any helper functions here
