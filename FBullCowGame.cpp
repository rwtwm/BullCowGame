#pragma once

#include "FBullCowGame.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include <cstdlib>

#define TMap std::map

using FString = std::string;
using int32 = int;


//Constructor
FBullCowGame::FBullCowGame()
{
	//Seed the random number generator for the word selection
	srand(time(NULL));
}


FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++; 
	
	FBullCowCount MyBullCowCount;

	int32 GuessLength = Guess.length();
	int32 HiddenWordLength = MyHiddenWord.length();

	//loop through every letter in Guess
	for (int32 i = 0; i < GuessLength; i++)
	{
		
		//Loop through every letter in HiddenWord
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j]) {
				
				if (i == j) {
					MyBullCowCount.Bulls++;
				} else {
					MyBullCowCount.Cows++;
				}

			}
		}
		
	}
	if (MyBullCowCount.Bulls == HiddenWordLength)
	{
		bIsGameWon = true;
	}
	
	return MyBullCowCount;
}

void FBullCowGame::SetDifficultyAndWord()
{
	//Get the user to determine the length of the isogram
	int32 Difficulty = ChooseDifficulty();
	
	//Select the dictionary with the required word length
	std::fstream Dictionary;
	Dictionary.open(CreateDictionaryName(Difficulty));

	//Find the number of lines in the dictionary
	int32 DictionaryLines = 0;
	DictionaryLines = CountLinesInDict(Dictionary);
	
	//choose a random word by randomly selecting a line number
	int32 ChosenWordLine = (rand() % DictionaryLines) + 1;
	
	//set the word as the hidden word 
	MyHiddenWord = RetreiveWordFromDictionary(Dictionary, ChosenWordLine);
}


//Currently adds the number given to the dictionary name. 
//Could be enhanced to have diffculty levels spanning a range of dictionaries. 
FString FBullCowGame::CreateDictionaryName(int32 Difficulty)
{
	FString FileName = "isograms";
	FileName.append(std::to_string(Difficulty));
	FileName.append(".txt");
	
	return FileName;
}

void FBullCowGame::Reset()
{
	GuessedWords = {};
	SetDifficultyAndWord();
	MyCurrentTry = 1;
	bIsGameWon = false;


	return;
}

//TODO Complete function defintion
bool FBullCowGame::IsIsogram(FString Guess) const
{
	bool bIsIsogram = true;
	TMap <char, bool> LetterSeen;
	
	for (auto Letter : Guess) //Loop through each character in the Guess
	{
		Letter = tolower(Letter);
		
		if (LetterSeen[Letter])
		{
			bIsIsogram = false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
			
	}

	return bIsIsogram;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	if (Guess.length()==0)
	{
		return true;
	}
	for (auto Letter : Guess) //Loop through all characters in guess
	{	
		if (Letter != tolower(Letter))
		{
			return false;
		}
			
	}
	
	return true;
}

bool FBullCowGame::IsGuessed(FString Guess) 
{
	
	if (GuessedWords[Guess])
	{
		return true;
	}
	else
	{
		GuessedWords[Guess] = true;
		return false;
	}

}

int32 FBullCowGame::ChooseDifficulty()
{
	int32 Difficulty = 0;
	bool IsDifficultyValid = false;
	FString TempInput = "";

	do 
	{
		std::cout << "Please choose the length of the hidden word (enter a number between 3 and 14): " << std::endl;

		std::getline(std::cin, TempInput);
		
		try 
		{
			Difficulty = std::stoi(TempInput);

			if (Difficulty > 2 && Difficulty < 15)
			{
				IsDifficultyValid = true;
			}


		}
		catch(std::invalid_argument){}


	
	} while (!IsDifficultyValid);

	return Difficulty;
}

int32 FBullCowGame::CountLinesInDict(std::fstream &Dictionary)
{
	int32 LineCount = 0;
	FString line;
	while (std::getline(Dictionary, line))
	{
		LineCount++;
	}

	Dictionary.clear();
	Dictionary.seekg(0, Dictionary.beg);

	return LineCount;
}

//Passing the dictionary is a bit messy. Could be refactored by creating a dictionary manager class. 
FString FBullCowGame::RetreiveWordFromDictionary(std::fstream &Dictionary, int32 LineNumber)
{
	int32 LineCount = 0;
	FString Line;

	do 
	{
		std::getline(Dictionary, Line);
		LineCount++;
	} while (LineCount < LineNumber);

	FString LowerLine = "";

	for (auto Letter : Line)
	{
		LowerLine += tolower(Letter);
	}

	return LowerLine;
}



//The number of tries is tied to the hidden word length
int32 FBullCowGame::GetMaxTries() const
{
	return (GetHiddenWordLength() * 3) - 4;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if ( ! IsIsogram(Guess) )// if is not isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (! IsLowercase(Guess)) //if is not lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) 
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (IsGuessed(Guess)) //check is guess already used
	{
		return EGuessStatus::Previous_Guess;
	}
	else
	{
		return EGuessStatus::OK;
	}
		
}


bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}
