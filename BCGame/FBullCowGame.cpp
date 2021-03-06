#include "FBullCowGame.h"
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#define TMap std::map
using namespace std;
using int32 = int;
using Fstring = string;


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}

int32 FBullCowGame::GetMaxTries() const { 
    TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, { 4,7 }, {5,10}, {6, 13}, {7, 16}, {8, 19}, {9,22}, {10, 25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

FBullCowGame::FBullCowGame() { Reset(); }

void FBullCowGame::Reset()
{
    //TODO hint system
    
    srand(unsigned(time(NULL)));
    int randNum;
    
    if (difchoice == 1)
    {
        Difficulty = "EASY";
    ifstream hidden_file_easy("hiddeneasy.txt");
        Fstring easyRand[ARRAYSIZE];
        for(int i = 0; i < ARRAYSIZE; i++)
            getline(hidden_file_easy, easyRand[i]);
        randNum = rand() % ARRAYSIZE;
        MyHiddenWord = easyRand[randNum];
    }
    else if (difchoice == 2)
    {
        Difficulty = "MEDIUM";
        ifstream hidden_file_med("hiddenmedium.txt");
        Fstring medRand[ARRAYSIZE];
        for (int i = 0; i < ARRAYSIZE; i++)
            getline(hidden_file_med, medRand[i]);
        randNum = rand() % ARRAYSIZE;
        MyHiddenWord = medRand[randNum];
    }
    else if (difchoice == 3)
    {
        Difficulty = "HARD";
        ifstream hidden_file_hard("hiddenhard.txt");
        Fstring hardRand[ARRAYSIZE];
        for (int i = 0; i < ARRAYSIZE; i++)
            getline(hidden_file_hard, hardRand[i]);
        randNum = rand() % ARRAYSIZE;
        MyHiddenWord = hardRand[randNum];

    }
    else if (difchoice == 4)
    {
        Difficulty = "VERY HARD";
        ifstream hidden_file_vhard("hiddenveryhard.txt");
        Fstring vhardRand[ARRAYSIZE];
        for (int i = 0; i < ARRAYSIZE; i++)
            getline(hidden_file_vhard, vhardRand[i]);
        randNum = rand() % ARRAYSIZE;
        MyHiddenWord = vhardRand[randNum];
    }
    
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isnt isogram, 
	{
		return EGuessStatus::Not_Isogram; 

	}
	else if (!IsLowercase(Guess)) // if the guess isnt all lowercase TODO write function
	{
		return EGuessStatus::Not_Lowercase;
	}
		
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else //otherwise 
	{
		return EGuessStatus::OK;
	}
}

// received a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if they match then
				if (MHWChar == GChar) 
				{
					//increment bulls if they're in the same place
					BullCowCount.Bulls++;
				}
				else 
				 {
					BullCowCount.Cows++;
				}
					//increment cows if not
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;

	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter word as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word)	//for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) { return false; } // if the letter is in the map
		else { LetterSeen[Letter] = true; }
			
	}
	return true;
}
bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {//if not a lowercase letter
			return false;

		}
		return true;
	}
    return true;
}