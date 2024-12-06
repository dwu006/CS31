#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int MAXWORDS = 8000;

const char WORDFILENAME[] = "smallwords.txt";
    // Windows users:  Use / instead of \ for pathname separators.

// function that runs one round of the game
int runOneRound(const char words[][7], int nWords, int wordnum)
{
    if(nWords < 1 || wordnum < 0 || wordnum >= nWords) {return -1;} // returns -1 if no words in array, if index of selected word is less than 0 or greater than the array size
    char guess[MAXWORDLEN+1];
    int stars = 0, planets = 0, guessCount = 0;
    do{
        do
        {
            char str[100];
            cout << "Trial word: ";
            cin.getline(str, 100);
            while(strlen(str) > MAXWORDLEN){ // loop and ask user for an appropriate guess word that isn't too long or too short
                cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
                cout << "Trial word: "; 
                cin.getline(str, 100);
            }
            strcpy(guess, str); // if guess is appropriate len copy to guess
            bool letter = true;
            // checks if guess contains all lowercase letters
            for(size_t i = 0; i < strlen(guess); i++)
            {
                if(!islower(guess[i]) || strlen(guess) < 4 || strlen(guess) > 6) //sets letter to false if there isnt lowercase or len <4 or >6
                {
                    letter = false;
                    break;   
                }
            }
            
            bool exist = true;
            for(size_t i = 0; i < nWords; i++)
            {
                if(strcmp(words[i], guess) == 0){exist = true; break;} // checks if guess is in word bank
                else{exist = false;}
            }

            //using above bool values determine if the word is valid or not
            if(!letter){cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;} 
            else if(exist){break;}
            else{cout << "I don't know that word." << endl;}
            
        }while(true);
        guessCount++; // increase guess count

        // 2 bool arrays to check whether each letter is star or planet
        bool starCount[MAXWORDLEN+1] = {false}; 
        bool planetCount[MAXWORDLEN+1] = {false};
        for(size_t i = 0; i < strlen(guess); i++){
            if(words[wordnum][i] == guess[i]){stars++; starCount[i] = true;}} // count number of stars and set bool arr to correct values

        for(size_t j = 0; j < strlen(guess); j++)
        {              
            if(strchr(words[wordnum], guess[j]) != NULL && !starCount[j]) //if the letter is in word and not a star
            { 
                for(size_t k = 0; k < strlen(guess); k++) 
                {   
                    // increase planets and sets planetCount arr to true if letter isnt a star equal to letter in num and not a planet from before
                    if(!starCount[k] && words[wordnum][k] == guess[j] && !planetCount[k]) {planets++; planetCount[k] = true; break;}
                }
            } 
        }

        if(stars == strlen(words[wordnum])){break;} //if amount of stars is equal to len of word then you gussed it!
        cout << "Stars: " << stars << ", Planets: " << planets << endl;
        stars = 0, planets = 0; // reset count for next guess

    }while(strcmp(guess, words[wordnum]));
    
    return guessCount;
}

int main()
{
    char w[MAXWORDS][MAXWORDLEN+1];
    int n = getWords(w, 8000, WORDFILENAME);
    if (n < 1) {cout << "No words were loaded, so I can't play the game."; exit(0);} // check if there are words in array

    int numRounds;
    cout << "How many rounds do you want to play? "; // ask user for number of rounds
    cin >> numRounds;
    cin.ignore(1000, '\n');

    if(numRounds <= 0) {cout << "The number of rounds must be positive"; exit(0);} // check if number of Rounds is positive
    else{cout << endl;}

    int min = 0, max = 0;
    double average = 0;

    for(size_t i = 1; i <= numRounds; i++)
    {   
        cout << "Round " << i << endl;
        int randomNum = randInt(0, n-1); //generates random number for random word
        cout << "The secret word is " << strlen(w[randomNum]) << " letters long." << endl;
        int numGuess = runOneRound(w, MAXWORDS, randomNum);   // returns number of guesses to guess the word
        if(i == 1){min = numGuess, max = numGuess;}
        if(numGuess > 1){cout << "You got it in " << numGuess << " tries." << endl;}
        else if(numGuess == 1){cout << "You got it in 1 try." << endl;}
        if(numGuess < min){min = numGuess;} // determiens of numGuess is max, min
        else if(numGuess > max){max = numGuess;}
        average = (average * (i-1) + numGuess) / i; // calculates average by using average value from previous rounds
        cout.setf(ios::fixed); // sets digits after decimal to 2
	    cout.precision(2);
        cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl << endl;
    }
}