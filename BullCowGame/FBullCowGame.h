/*
The game logic(no view code or direct user interaction)
The game is a simple guess the word game based on bull cow hints
*/
#pragma once
#include<string>

//to be Unreal friendly
using FString = std::string;
using int32 = int;

//all values initialized as 0
struct FBullCowCount {
	int32 Bulls=0;
	int32 Cows=0; //by default, members are public
};

enum class EGuessStatus {//strong enum, OK is valid inside the scope
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor
	int32 GetMaxTries() const; //a guard to control the change of class
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidilty(FString) const;
	bool IsIsograme(FString) const;
	bool IsLowerCase(FString) const;
	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);
	

private:
	int32 MyCurrentTry=1;
	int32 MyMaxTries=5;
	FString MyHiddenWord;
	bool bGameIsWon;
};