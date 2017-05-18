/* This is the console executable, that makes use of the BullCow class.
This acts as the 'view' in a MVC pattern, and is responsible for all user interaction.
For game logic see FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FString = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FString GetValidGuess();
bool AskToPlayAgain();


FBullCowGame BCGame;


int main() 
{
	bool bPlayAgain = false;
	do
	{
		std::cout << std::endl;
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0;
}


void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	for (int32 i = 0; i < MaxTries; i++) // TODO change FOR loop to a WHILE loop while validating tries
	{
		FString Guess = GetValidGuess();
		
		// submit the valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << "  Cows: " << BullCowCount.Cows << "\n\n";
	}
	// TODO summarize game
}

// loop continuosly until the user gives a valid guess
FString GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FString Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating the letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your Guess in lowercase letters.\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n): ";
	FString Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}