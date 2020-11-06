#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "HashTable.h"

/**
 * Printing of the introduction of the game.
 */
void firstMessage(){
    printf("**************************************************\n");
    printf("***          Welcome to (Evil) Hangman         ***\n");
    printf("*** You are going to play against the computer ***\n");
    printf("**************************************************\n");
}

/**
 * A function to give the number of guesses available for the player
 * and also check that the input is correct
 * @return the number of guesses available
 */
int giveGuessTries(){

    //TotalGuesses, with checking
    int totalGuesses = -1;
    printf("\nHow many total guesses? ");

    int secondTry =0;

    //Making sure not to go into an infinite loop when user inputs a char
    do{
        if(secondTry == 1){
            printf("Wrong Input. Give a positive number: ");
        }
        fflush(stdout);
        if(scanf("%d",&totalGuesses) != 1){
            totalGuesses = -1;
            int c;
            while((c= getchar()) != EOF && c != '\n');

            if(c == EOF){

            }
        }
        secondTry = 1;
    } while(totalGuesses <= 0);

    printf("\n-------------------------------\n");

    return totalGuesses;

}

/**
 * Gets the word length from the file and removes that number from the file
 * so we are left with only the words
 * @return the word length
 */
int getWordLength(char *arg){

    //Read the text file
    FILE *fp = NULL;
    fp = fopen(arg,"r");

    if(fp == NULL){
        printf("Unable to open");
        exit(-1);
    }

    int wordl = 0;
    fscanf(fp,"%d",&wordl);

    fclose(fp);

    return wordl;

}

/**
 * The function checks if the letter given was already given or not
 * and prints the appropriate message
 * @param arr the array of the alphabet
 * @param letter the letter given
 */
int checkLetterGiven(char arr[],char letter){

    return (arr[letter - 'a']++) != 0;

}

/**
 * The function makes sure the words of the file and the letter given of the user have
 * the same case. If not it makes the user letter match the text file case
 * @param arg the file parameter
 * @letter the letter that the user gave
 */
void CheckLetterCaps(char *arg,char *letter){

    //Read the text file
    FILE *fp = NULL;
    fp = fopen(arg,"r");

    if(fp == NULL){
        printf("Unable to open");
        exit(-1);
    }

    //Used to get rid of the number in the file
    int temp = 0;
    fscanf(fp,"%d",&temp);

    char letterSample;

    //Get a letter from the word to see if its caps or not
    fscanf(fp,"%c",&letterSample);

    fclose(fp);

    //If words are caps make user letter caps
    if(letterSample <= 90){
        if(*letter>= 97){
            *letter = *letter - 32;
        }
    }
    //If words are lower case make user letter lower case
    else if(letterSample >= 97){
        if(*letter<=90){
            *letter = *letter + 32;
        }
    }

}

/**
 * This function makes sure the letter given by the user is valid and returns it
 * @return the valid letter given by the user
 */
char CheckLetter(){

    printf("Guess a letter: ");

    char letter;

    //This one takes the character without taking the enter character
    scanf(" %c",&letter);

    //While the letter is not a valid letter
    while(!(letter>=65 && letter<=90) || !(letter>=97 && letter<=122) ){
        printf("That is not a letter. Please give a letter: ");
        scanf(" %c",&letter);
    }

    return letter;

}

/**
 * The main function that does the function calling
 * @param argc
 * @param argv
 * @return
 */
int main(int argc,char *argv[]) {

    //Intro Message
    firstMessage();

    //Give the number of guesses
    int totalGuesses = giveGuessTries();

    //Gets the word length from the file
    if(argc != 2){
        printf("Wrong argument files. You need to input 1 text file.");
        exit(-1);
    }

    int wordl = getWordLength(argv[1]);

    //The string used for printing our word progress
    char wordProgress[wordl];

    for(int i=0;i<wordl;i++){
        wordProgress[i] = '_';
    }
    wordProgress[wordl] = '\0';

    //Testing
    int gameEnd = 0;

    //Making sure the first time we read from the file and no other times
    int firstRead = 1;

    //An array used to keep track which letters the player has said so far
    //Initialized all with 0, when value becomes 1 it means we picked that letter
    char alphabetArray[26] = {0};

    //Main loop of the hangman game
    while(gameEnd!=1){

    printf("Progress: %s\n",wordProgress);
    printf("Number of Guesses: %d\n",totalGuesses);


    char letter;
    //Get the letter that the user gave, also do the appropriate checkings
    letter = CheckLetter();

    //Change the case of the letter if needed to match the text file
    CheckLetterCaps(argv[1],&letter);

    //If user gave the letter before, print an error message and let him put a new letter
    if(checkLetterGiven(alphabetArray,letter)){
        printf("Letter %c was given before\n",letter);
        printf("\n-------------------------------\n");
        continue;
    }

    //The maxListSize is used to keep track of the size of the largest list every time
    int maxListSize = 0;

    //Create the max list pointer
    LIST *maxlist = NULL;

    //Create the hash table pointer
    HASHTABLE *ht = NULL;

    //Create the char array pointer
    char **array = NULL;

    //Create an int that indicates every time if the user has guessed a new letter or not
    int guessedLetter = 0;

    //The creation of the hash table every time

    //Read from file only the first time
    if(firstRead){

        //Read the words and put them in the hash table
        //ht now points to the hash table
        ht = ReadFile(argv[1],wordl,letter);

        //Finds the max list and returns a pointer to it and also calculates the max list size
        maxlist = findMaxList(ht,wordl,&maxListSize,&guessedLetter);

        //Saves the contents of the list to the array and returns a pointer pointing to that array
        array = saveListToArray(maxlist,maxListSize);

        //Delete from memory the whole hash table
        deletePreviousHash(ht);

        firstRead = 0;
    }
    //Read the array so far
    else{

        //Read the array, create the hash table and return a pointer pointing to it
        ht = ReadFromArray(array,wordl,letter,maxListSize);

        //Finds the max list and returns a pointer to it and also calculates the max list size
        maxlist = findMaxList(ht,wordl,&maxListSize,&guessedLetter);

        //Saves the contents of the list to the array and returns a pointer pointing to that array
        array = saveListToArray(maxlist,maxListSize);

        //Delete from memory the whole hash table
        deletePreviousHash(ht);

    }

    //Decreasing every time the guesses
    totalGuesses--;

    //Conditions to end the game

    //Running out of tries
    if(totalGuesses == 0){
        gameEnd=1;
        printf("**************************************************\n");
        printf("You run out of guesses. You lost\n");
        //Just printing a random word that is in the first array slot
        printf("The secret word was: %s\n",array[0]);
        printf("**************************************************\n");

    }

    //Finding the word and winning the game
    if(maxListSize==1){
        gameEnd=1;
        printf("**************************************************\n");
        printf("Congratulations, you win the game\n");
        printf("The secret word is: %s",array[0]);
        printf("**************************************************");
    }

    else {
        //Print message if user guessed a letter
        if(guessedLetter){

            //We need to update our secret word

            //Create a temporary word to update our secret word
            char tempword[wordl+1];

            tempword[wordl+1] = '\0';

            //It can be any word from the array
            strcpy(tempword,array[0]);

            for(int i=0;i<wordl;i++){
                //If our temporary word has a letter equal to the letter the user guessed correctly,
                //We update our secret word
                if(tempword[i] == letter){
                    wordProgress[i] = letter;
                }
            }

            //Print message that user guessed a letter
            printf("You guessed a letter correctly");
        }
        //Print message if user didn't guess a letter
        else{
            printf("%c not in secret word",letter);
        }

        printf("\n\n-------------------------------\n");
    }

    }

    return 0;
}
