#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {
	Reset();
} 

void FBullCowGame::Reset(){ 

	const FString HIDDEN_WORD = "plan";

	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	
	if (!IsIsogram(Guess)) {// if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;  
	}
	else if (!IsLowercase(Guess)) { // if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength()) {// if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
	

}

// receive a VALID guess, incriments turn, and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = (int32) MyHiddenWord.length();// assuming same length as guess
	
	//loop through all letters in the hidden word	
	for (int32 i = 0; i < WordLength; i++) {
		//compare letters against the guess
		for (int32 j = 0;j < WordLength;j++) {
			//if they match then
			if (Guess[j] == MyHiddenWord[i]) {
				// if they're in same place
				if (j == i) {
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

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter word as isograms
	if (Word.length() <= 1) {
		return true;
	}
	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)		// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {	// if the letter is in the map
			return false;	// we do NOT have an isogram
		}
		else {	
			LetterSeen[Letter] = true;// add the letter to the map as seen
		}	
				
	}
	return true; // for example in case where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const {

	for (auto Letter : Word) { 
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

int FBullCowGame::GetMaxTries() const{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int FBullCowGame::GetCurrentTry() const{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return  (int32) MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const{
	return bGameIsWon;
}


