#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: Tyler Keller

    last modified: 10/24/2021
*/

/*  For the family shit,
 *
 * set up a while loop that only ends when letter count in word is 0, and you're at the end of the list
 *
 * Could also set up for near end of the list and shave time off.
 *
 * for the other while loops, have one for setting them into families based off
 * both the count of letters in the world and the positions, may need to set up a class for this
 *
 *
 *
 *
 *
 *
 *
 */

#include <string>
#include <unordered_set>
#include <map>
#include <vector>
#include <set>


/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

using namespace std;

class hangman {
public:
    using Family = set<string>;

    vector<string> dictionary;

    map<basic_string<char>, Family> word_families;

    Family max_family;

    string cur_word_state;

    set<char> guessed_chars;

    int num_guesses;

    int word_len;

    bool see_words;

    hangman();

    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int num_guesses_param, bool see_word_param, int word_len_param);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

private:
    
};

#endif
