#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 8}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "bench";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	for (int32 i = 0; i < WordLength; i++) 
	{
		for (int32 j = 0; j < WordLength; j++)
		{
			if (MyHiddenWord[i] == Guess[j])
			{
				if (i == j) 
				{
					BullCowCount.Bulls++;
				}
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) 
		{ 
			return false; 
		} 
		else 
		{ 
			LetterSeen[Letter] = true; 
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{	
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}
