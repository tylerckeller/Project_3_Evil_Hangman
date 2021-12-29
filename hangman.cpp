/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Tyler Keller

    last modified: 10/24/2021
*/

#include "hangman.h"
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

// constructor
hangman::hangman() {

    ifstream fin;

    fin.open("dictionary.txt");

    //add each word from dictionary.txt to public dictionary set in class
    while (!fin.eof()) {

        string s;

        getline(fin, s);

        dictionary.push_back(s);

    }

}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses_param, bool see_words_param, int word_len_param) {

    num_guesses = num_guesses_param;

    see_words = see_words_param;

    word_len = word_len_param;

    for (int i = 0; i < word_len; i++) {

        cur_word_state += "-";

    }
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {

    guessed_chars.insert(c);

    for (const string& str : dictionary) {

        string temp = str;

        for (int i = 0; i < temp.length(); i++) {

            if (temp[i] != c) {

                temp[i] = '-';

            }

        }

        auto it = word_families.find(temp);

        if (it == word_families.end()) {

            Family new_family;

            new_family.insert(str);

            word_families[temp] = new_family;

        } else {

            it->second.insert(str);

        }

    }

    using pair_type = decltype(word_families)::value_type;

    auto max_pair = max_element

            (

                word_families.begin(), word_families.end(),

                [] (const pair_type & p1, const pair_type & p2) {
                    return p1.second.size() < p2.second.size();
                }

            );

    max_family = max_pair->second;

    int i = 0;

    for (char c : max_pair->first) {

        if (c != '-') {

            cur_word_state[i] = c;

        }

        i++;

    }

    dictionary = vector<string>(max_family.begin(), max_family.end());

    word_families.clear();

    if (cur_word_state.find(c) != string::npos) {

        return true;

    }

    num_guesses--;

    return false;

}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return cur_word_state;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return num_guesses;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {

    string str;

    for (const auto & it : guessed_chars) {

        str += it;

    }

    return str;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {

    return (guessed_chars.find(c) != guessed_chars.end());

}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {

    return (cur_word_state.find('-') == string::npos);

}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    if (num_guesses == 0) {

        return true;

    }

    return false;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {

    return dictionary[0];

}


