#pragma once

/*

*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;


//Function prototypes so they are recognised in main
//Once declared function can be implemented anywhere in the code
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuessScore(FBullCowCount);
bool AskToPlayAgain();
void PrintGameSummary(bool);

void RunTests();

//We can define global variables here
FBullCowGame BCGame;


//First entry of the compiler into the program
int main()
{
	bool bPlayAgain = false;

	do
	{
		BCGame.Reset();
		PrintIntro();
		PlayGame();
		PrintGameSummary( BCGame.IsGameWon() );
		bPlayAgain = AskToPlayAgain();	

	} while (bPlayAgain);

	//main is an int, so this is required
	return 0;
}

void RunTests()
{
	BCGame.SetDifficultyAndWord();
}


void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";

	//Loops through the main game asking for guesses 
	//until the guess word matches the hidden word
	//or the player is out of tries		
	while( ! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Guess = GetValidGuess();
		
		FBullCowCount myBullCowCount = BCGame.SubmitGuess(Guess);
		PrintGuessScore(myBullCowCount);
	}

	return;
}

//introduce the game
void PrintIntro()
{
	int32 WordLength = BCGame.GetHiddenWordLength();

	std::cout << "\nWelcome to bulls and cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << WordLength;
	std::cout << " letter isogram I'm thinking of?" << std::endl;

	return;
}


//Loop until the user provides a valid guess
FText GetValidGuess()
{
	EGuessStatus GuessStatus = EGuessStatus::Initial_Status;
	FText Guess = "";

	do	{

		std::cout << "Try " << BCGame.GetCurrentTry() << ". Please make a guess: ";
		getline(std::cin, Guess);

		GuessStatus = BCGame.CheckGuessValidity(Guess);

		switch (GuessStatus)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
			std::cout << " letter word" << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase." << std::endl;
			break;
		case EGuessStatus::Previous_Guess:
			std::cout << "You have already tried that!" << std::endl;
			break;
		
		default:
			break;
		}

	} while (GuessStatus != EGuessStatus::OK);

	return Guess;
}

void PrintGuessScore(FBullCowCount BCCount)
{
	std::cout<< "Your word has " << BCCount.Bulls << " Bulls." << std::endl;
	std::cout << "Your word has " << BCCount.Cows << " Cows." << std::endl;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";

	FText Response = "";
	getline(std::cin, Response);

	bool PlayAgain = false;
	if (Response[0] == 'Y' || Response[0] == 'y')
	{
		PlayAgain = true;
	}
	
	return PlayAgain;
}

void PrintGameSummary(bool bIsGameWon)
{
	if (bIsGameWon)
	{
		std::cout << "Congratulations, You got it right!" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time!" << std::endl;
	}
}
