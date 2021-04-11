// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

 // When the game starts 
void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();
    
    HiddenWord = TEXT("rise");
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Setting Up Game   
    InitGame();

    for (int32 i = 0; i < 4; i++) {
        PrintLine(TEXT("%i"), Words[i]);
    }
}

void UBullCowCartridge::OnInput(const FString& Input) {

    if (bGameOver) {
        ClearScreen();
        InitGame();
    } else {
        // Checking Player's Guess

        ProcessGuess(Input);
    }

    // check If Isogram
    // Check Right Number Of Characters
    // Remove Life
    // Check if Lives > 0
    // If It is Higher than 0, keep playing
    // If It's Lower than 0, show game over screen and ask to play again?
    //
}


void UBullCowCartridge::InitGame() {

    PrintLine(FString::Printf(TEXT("Hello There, Welcome to the bulls & cows game,")));
    PrintLine(FString::Printf(TEXT("There is %i possible words that will be used"), Words.Num()));
    PrintLine(FString::Printf(TEXT("The HiddenWord Is %s, It's %i characters"), *HiddenWord, HiddenWord.Len())); // Debug Line
    PrintLine(FString::Printf(TEXT("Guess The %i Letter isomorphic Word"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("You Have %i Lives, Dont use them Up!"), Lives));
    PrintLine(FString::Printf(TEXT("type the word and press enter")));


//    const TCHAR HW[] = TEXT("plums");
//    PrintLine(TEXT("The First Character Of The Word Is: %c "), HiddenWord[0]);
//    PrintLine(TEXT("The 4th Character Of the word: %c"), HW[3]);
    IsIsogram(HiddenWord);
}

bool UBullCowCartridge::IsIsogram(FString Word) const {

    for (int32 Index = 0; Index < Word.Len(); Index++) {
        for (int32 Comparison = 0; Comparison < Word.Len(); Comparison++) {
            if (Word[Index] == Word[Comparison]) {
                return false;
            }
        }
    }
    return true;

    //int32 Index = 0;

    //for (Comparison = Index + 1; Comparison < Word.Len(); Comparison++) {
    //    if (Word[Index] == Word[Comparison]) {
    //        return false;
    //    } else {
    //        Index++;
    //    }
    //}
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
    if (Guess == HiddenWord) {
        PrintLine(FString::Printf(TEXT("You Win!")));
        return;
    }


    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(FString::Printf(TEXT("Wrong Word, You Have %i Lives Left, Try Again"), Lives));
        PrintLine(FString::Printf(TEXT("The Hidden Word You Have To Guess Is %i letters long"), HiddenWord.Len()));
        return;
    }

    if (!IsIsogram(Guess)) {

        PrintLine(FString::Printf(TEXT("You Cant Have Any Repeating Letters. Guess Again")));
        return;
    }

    Lives--;
    if (Lives > 0) {
        if (Guess.Len() != HiddenWord.Len()) {
            PrintLine(FString::Printf(TEXT("Wrong Word, You Have %i Lives Left, Try Again"), Lives));
        }
    }
    else {
        //PrintLine(TEXT("You Have 0 lives Left, The Hidden Word Is %i"), HiddenWord);
        EndGame();
    }
}


void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(FString::Printf(TEXT("Press Enter to play again")));
}


