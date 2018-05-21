#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {2,3},{3,5},{4,7},{5,10},{6,16},{7,20},{8,24} }; //the guesses changed depends on the length
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset() {
	
	const FString HIDDEN_WORD = "air"; //this MUST be a isogram
	MyHiddenWord = HIDDEN_WORD; 

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidilty(FString Guess) const{
	
	if (!IsIsograme(Guess)) { //if the guess is not isgram, return an error
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowerCase(Guess)) { //if the guess if not all lowercase, return an error
		return EGuessStatus::Not_Lowercase; 
	}	
	else if (Guess.length() != GetHiddenWordLength()) { //if the guess length is wrong, return an error
		return EGuessStatus::Wrong_Length;
	}	
	else { 
		return EGuessStatus::OK; 
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount; //the name of the type

	//loop through all letters in the hidden word, i: my hidden word character
	int32 WordLength = MyHiddenWord.length(); //assume same length as guess
	for (int32 MHChar = 0; MHChar < WordLength; MHChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) { //compare letters against the guess, j: guess character
			if (Guess[GChar]==MyHiddenWord[MHChar]) {		
				if (MHChar == GChar) {	//if they're in the same place			 
					BullCowCount.Bulls++;
				}		
				else {	
					BullCowCount.Cows++;
				}
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

bool FBullCowGame::IsIsograme(FString Word) const{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {
	for (auto Letter : Word) {
		if (islower(Letter)) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}
