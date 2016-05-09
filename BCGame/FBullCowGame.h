#pragma once
#include <string>

using namespace std;
using int32 = int;
using FString = std::string;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor
    # define ARRAYSIZE 15
	void Reset(); 
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
    int32 difchoice;
    FString Difficulty;
	FBullCowCount SubmitValidGuess(FString);
    FString MyHiddenWord;

private:
    int32 MyCurrentTry;
    FString RandWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};