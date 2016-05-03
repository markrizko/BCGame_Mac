/* This is the console exe that makes use of the bull cow class
This acts as the view in a MVC pattern and is responsible for all user interaction. 
For game logic see the FBullCowGame class
*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <fstream>

using namespace std;

using FText = string;
using int32 = int;

void PrintIntro();
void GameDifficulty();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame; //instantiate a new game

int main()

{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while
		(bPlayAgain);
	return 0;
}



//introduce the game 
void PrintIntro() 
{
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << endl;
	cout << "          }   {         ___ " << endl;
	cout << "          (o o)        (o o) " << endl;
	cout << "   /-------\\ /          \\ /-------\\ " << endl;
	cout << "  / | BULL |O            O| COW  | \\ " << endl;
	cout << " *  |-,--- |              |------|  * " << endl;
	cout << "    ^      ^              ^      ^ " << endl;
	cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	cout << " letter isogram I'm thinking of?\n\n";
	cout << endl;
	return;
}
//get the guess and print it back to you

FText GetValidGuess() 
{
	FText Guess;
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {


		int32 CurrentTry = BCGame.GetCurrentTry();
		cout << "Try " << CurrentTry++ << " of "<< BCGame.GetMaxTries()<<". Take a swag: ";
		getline(cin, Guess);
		

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			cout << "Make sure you have entered a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "Please enter an all-lowercase word.\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}
bool AskToPlayAgain()
{
	cout << "Do you want to play again?(y/n)\n";
		FText Response = "";
		getline(cin, Response);
		cout << endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void GameDifficulty() {
    cout << "Please choose a difficulty.\n[EASY: 1]\n[MEDIUM: 2]\n[HARD: 3]\n[EXTREME: 4]\n";
    cout << "Difficulty: ";
    cin >> BCGame.difchoice;
    cout << endl << endl;
}

void PlayGame()
{
    GameDifficulty();
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	
	//loop for number of turns while the game is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		cout << "Bulls = " << BullCowCount.Bulls;
		cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { cout << "Congrats!! You win!\n\n"; }
	else { cout << "You lost :/.. Do you wanna try again?\n\n"; }
}