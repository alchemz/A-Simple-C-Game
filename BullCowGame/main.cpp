/*
FText will be used inside main method, for the output of user interaction.
FString will be used inside FBullCowGame class method, for the usage of string
int32 will be used to replace the integer type, because we will work cross platform.
only for the main loop, which will be called by the OS
*/
#pragma once

#include <iostream> //preprocessors
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes outside of class
FText GetValidGuess();
void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //FBullCowGame is the template, intantiate a new game

int main() {
	bool PlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PlayAgain = AskToPlayAgain();
	} while (PlayAgain);

	return 0;
}

void PrintIntro() {
	std::cout << "Welcome to the Bull and Cow\n";
	std::cout <<" '\v/`    |:+:|    |:+:|   "<< std::endl;
	std::cout <<"(o 0)    (o:o)    (o:o)  " << std::endl;
    std::cout <<" (_)      (:)      (:)   " << std::endl;
	std::cout << "The world length is: " << BCGame.GetHiddenWordLength() << std::endl;
	std::cout << "The max tries is: " << BCGame.GetMaxTries() << std::endl;
}

//plays a single game util completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	while(!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= MaxTries)){	
		FText Guess = GetValidGuess(); 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);// submit the valid guess to the game, and receive count
		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << ". Cows= " << BullCowCount.Cows << "\n";
		std::cout << "Guesses left: " << MaxTries - BCGame.GetCurrentTry()+1<< std::endl;
	}

	PrintGameSummary();
}

FText GetValidGuess() { //loop continuelly, util the right guess
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "<<BCGame.GetMaxTries()<< ". Enter your guess: ";	
		std::getline(std::cin, Guess); //stop by space, be default

		Status = BCGame.CheckGuessValidilty(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter the guess in lower case.\n\n";
			break;
		default:
			break; //assume the guess is valid
		}
	} while (Status != EGuessStatus::OK);//keep looping util get no errors
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word(y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
	if (Response[0] == 'Y' || Response[0]=='y') {
		return true;
	}
	return false;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well done, you got the word!\n";
	}
	else {
		std::cout << "Do you wanna another try?\n";
	}
}




