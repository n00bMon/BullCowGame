#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;
	const FString HIDDEN_WORD = "ant";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}


bool FBullCowGame::IsGameWon() const
{
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) // if the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())// if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// recieves guess if VALID, increments turn, and returns count
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
	return BullCowCount;
}
