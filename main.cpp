/*
    main.cpp
        
    Implements the user interface for hangman.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Tyler Keller

    last modified: 10/24/2021
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

#include "hangman.h"

using namespace std;

// helper function prototypes
int get_integer(string msg); // return a positive integer
char get_letter(string msg); // return a valid lowercase letter
bool get_yesno(string msg);  // return true == yes / false == no
string trim(string s);          // remove leading/trailing whitespace

int main() {

    cout << "Welcome to Hangman!" << endl;
    cout << "===================" << endl << endl;

    // get the hangman object
    hangman game;

    vector<string> start_dict = game.dictionary;

    game.cur_word_state = "";
    
    // Keep playing the game until the user decides otherwise
    while (true) {

        game.dictionary = start_dict;

        int word_len = get_integer("How long do you want your word?");

        bool valid_word_len = false;

        //goes through dictionary set, valid word len set true if word with len of word_len is found
        for (string &s : game.dictionary) {

            if (s.length() == word_len) {

                valid_word_len = true;

            }

        }

        if (!valid_word_len) {

            cout << "Please enter a valid word length" << endl;

            continue;

        }

        vector<string> new_dict;

        for (const auto & it : game.dictionary) {

            if (it.length()==word_len) {

                new_dict.push_back(it);

            }

        }

        game.dictionary = new_dict;

        int num_guesses = get_integer("How many guesses would you like?");
        cout << endl;

        bool see_words = false;

        //bool see_words = get_yesno("Do you want to see how many words are left?");

        game.start_new_game(num_guesses, see_words, word_len);

        while (!game.is_won() && !game.is_lost()) {

            cout << "Your word is: " << game.get_display_word() << endl;

            string already_guessed = game.get_guessed_chars();

            if (already_guessed.empty()) {

                cout << "You have not yet guessed any letters." << endl;

            } else {

                cout << "You have already guessed these letters: ";
                cout << already_guessed << endl;

            }

            cout << "You have " << game.get_guesses_remaining();
            cout << " guesses remaining." << endl << endl;

            char guess = get_letter("What is your next guess?");

            while (game.was_char_guessed(guess)) {

                cout << endl << "You already guessed that!" << endl;
                guess = get_letter("What is your next guess?");

            }

            cout << endl;

            bool good_guess = game.process_guess(guess);

            if (see_words) {

                cout << "Words in chosen family: " << game.dictionary.size() << endl;

            }

            if (good_guess) {

                cout << "Good guess!" << endl;

            } else {

                cout << "Sorry, that letter isn't in the word." << endl;

            }

            if (game.is_won()) {

                cout << "Congratulations! You won the game!" << endl;

            }

            if (game.is_lost()) {

                cout << "Oh no! You lost!!!" << endl;
                cout << "My secret word was: " << game.get_hidden_word() << endl;

            }
        }

        cout << endl;

        if (!get_yesno("Would you like to play again (y/n)?")) break;

    }

    cout << endl << "Thank you for playing Hangman." << endl;

    return 0;
}

// Prompt for a positive integer response, re-prompting if invalid
// input is given. This is not super-robust - it really should work
// harder to filter out responses like "123foo", but oh well.
int get_integer(string msg) {
    while (true) {
        string input;    
        int result = 0;

        cout << msg << endl;
        getline(cin, input);

        result = atoi(input.c_str());
        if (result > 0) return result;

        cout << "I didn't understand that. Please enter a positive integer.";
        cout << endl;
    }
}
    
// Prompt for a letter of the alphabet, re-prompting if invalid
// input is given.
char get_letter(string msg) {
    while (true) {
        string input;    
 
        cout << msg << endl;
        getline(cin, input);

        input = trim(input);

        if (input.size() == 1) {
            char result = tolower(input[0]);
            if (result >= 'a' && result <= 'z') return result;
        }
        
        cout << "I didn't understand that. ";
        cout << "Please enter a letter of the alphabet.";
        cout << endl;
    }
}


// Prompt for a yes/no response, re-prompting if invalid
// input is given.
bool get_yesno(string msg) {
    while (true) {
        string input;    
 
        cout << msg << endl;
        getline(cin, input);

        input = trim(input);
        for (int i = 0; i < input.size(); i++) {
            input[i] = tolower(input[i]);
        }

        if (input == "y" || input == "yes") return true;
        if (input == "n" || input == "no") return false;
        
        cout << "I didn't understand that. ";
        cout << "Please enter y(es) or n(o).";
        cout << endl;
    }
}

string trim(string s) {
    int a, b;

    for (a = 0; a < s.size() && isspace(s[a]); a++);
    for (b = s.size() - 1; b >= a && isspace(s[b]); b--);
    
    return s.substr(a, b - a + 1);
}


