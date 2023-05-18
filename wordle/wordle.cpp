#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <map>
#include <limits>

using namespace std;

// guesser and marks are the key object here. 
// guesser is a 6-sized vector of char holding all possibles letter per final-word-letter. 
// In the begining, guesser is initialized with all 26 letters from the alphabet ordered by 
// letter frequencies (see link below)
// If a letter is not in the word, it is removed from this guesser object for all indices.
// If a letter is a correct position, all letters are removed but the correct one.
// If a letter is in the word but incorrect position, this letter is pushed to top priority
// for all other indices not yet found.

// Once guesser object is updated on each turn, we compute all letter marks per position.
// Formula is pretty simple:
// letter mark = guesser index or 100 if not found.  

// Then, we loop for all possible words, find the word with the lower mark (best probability)
// and print it. 

// Order by most common letters -> https://en.wikipedia.org/wiki/Letter_frequency
static vector<char> letters = {
    'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P','B','V','K','J','X','Q','Z'
};
static const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct Word {
    char word[6];
};
static vector<Word> all_words;
static vector<string> played;
static array<vector<char>, 6> guesser;
static array<map<char, int>, 6> marks;

void display() {
    cerr << "guesser\n";
    for (int i=0; i<6; ++i) {
        cerr << i << " ";
        for (auto letter: guesser[i]) {
            cerr << " " << letter;
        }
        cerr << '\n';
    }
    cerr << "marks:\n";
    for (int i=0; i<6; ++i) {
        cerr << i << " ";
        map<char, int>::iterator it;
        for (it = marks[i].begin(); it != marks[i].end(); ++it) {
            cerr << " " << it->first << ":" << it->second;
        }
        cerr << '\n';
    }
    cerr << endl;
}

void feed(string word, int idx, int state) {
    const auto letter = word[idx];

    if (state == 1) {
        // letter not in word, remove it from all possibilities
        for (int i=0; i<6; ++i)
            guesser[i].erase(remove(guesser[i].begin(), guesser[i].end(), letter), guesser[i].end());

    } else if (state == 2) {
        // letter in word but incorrect pos, top priority for all other letters not found
        for (int i=0; i<6; ++i) {
            if (i == idx)
                continue;
            if (guesser[i].size() == 1) // do not update letters already found
                continue;
            guesser[i].erase(remove(guesser[i].begin(), guesser[i].end(), letter), guesser[i].end());
            guesser[i].insert(guesser[i].begin(), letter);
        }

    } else if (state == 3) {
        // correct pos, remove all but current letter
        if (guesser[idx].size() > 1) {
            guesser[idx].clear();
            guesser[idx].push_back(letter);
        }
    }
}

void compute_letter_marks() {
    for (int i=0; i<6; ++i) {
        for (char c: alphabet) {
            auto it = find(guesser[i].begin(), guesser[i].end(), c);
            if (it != guesser[i].end()) {
                int index = it - guesser[i].begin();
                marks[i].at(c) = index;
            } else {
                marks[i].at(c) = 100;
            }
        }
    }
}

string find_next() {
    string nextw;
    int min_score = numeric_limits<int>::max();
    for (auto &w: all_words) {
        int word_mark = 0;
        for (int i=0; i<6; ++i) {
            const auto letter = w.word[i];
            word_mark += marks[i].at(letter);
        }
        if (word_mark < min_score) {
            string neww = string(w.word, 6);
            // cerr << "detected " << neww << " mark " << word_mark << "\n";
            if (find(played.begin(), played.end(), neww) == played.end()) {
                nextw = neww;
                min_score = word_mark;
            }
        }
    }
    return nextw;
}

int main()
{
    // init guesser
    for (int i=0; i<6; ++i) 
        guesser[i] = letters;

    // init marks
    for (int i=0; i<6; ++i) {
        for (auto &c: letters)
            marks[i].insert(pair<char, int>(c, 0));
    }

    reverse(letters.begin(), letters.end());
   
    int word_count; // Number of words in the word set
    cin >> word_count; cin.ignore();

    for (int i=0; i<word_count; ++i) {
        string word; // Word in the word set
        cin >> word; cin.ignore();
        Word w;
        memcpy(w.word, word.c_str(), 6);
        all_words.push_back(w);
    }
    
    string next_guess = string(all_words[0].word, 6);
    int turn = 1;

    while (turn < 30) {
        for (int i=0; i<6; ++i) {
            int state; // State of the letter of the corresponding position of previous guess
            cin >> state; cin.ignore();
            feed(next_guess, i, state);
        }
        
        compute_letter_marks();
        next_guess = find_next();
        cout << next_guess << endl;
        played.push_back(next_guess);
        ++turn;
    }
}