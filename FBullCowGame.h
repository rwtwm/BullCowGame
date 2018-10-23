#pragma once
#include <string>
#include <iostream>
#include<fstream>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

//Structures are public by default.
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Previous_Guess,
	Not_Lowercase,
	Initial_Status
};

class FBullCowGame
{
//This is the public interface of the class
public:
	FBullCowGame();		//Constructor

	bool IsGameWon() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const; 
	int32 GetHiddenWordLength() const;
	
	EGuessStatus CheckGuessValidity(FString);

	//Asks the player to choose the difficulty of the game and sets the hidden word accordingly
	void SetDifficultyAndWord();

	//If the guess is valid, this returns the score of the guess, 
	//and increments the turn counter
	FBullCowCount SubmitGuess(FString);
	void Reset();		//TODO improve return value 
	

//Private vars are initialised in constructor
private:
	int32 MyMaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
	TMap<FString, bool> GuessedWords;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsGuessed(FString);
	
	int32 ChooseDifficulty();
	FString CreateDictionaryName(int32);
	int32 CountLinesInDict(std::fstream &Dictionary);
	FString RetreiveWordFromDictionary(std::fstream &Dictionary, int32);
};


