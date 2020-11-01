#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void readDictionary(){

}

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

    return wordl;

}

/**
 * The function checks if the letter given was already given or not
 * and prints the appropriate message
 * @param arr the array of the alphabet
 * @param letter the letter given
 */
int checkLetterGiven(int arr[],char letter){

    //Making sure all letters are lowercase
    if(letter>=65 && letter<=90){
        letter = letter + 32;
    }

    //Increase the appropriate array slot for each letter
    for(char i='a';i<='z';i++){
        if(i==letter && arr[i-97] == 1){
            printf("Letter %c was given before",letter);
            return 0;
        }
        if(i==letter && arr[i-97] != 0){
            arr[i-97]++;
            return 1;
        }
    }
    return 0;


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

    //Main loop of the hangman game
    while(gameEnd!=1){

    printf("Progress: %s\n",wordProgress);
    printf("Number of Guesses: %d\n",totalGuesses);

    //An array used to keep track which letters the player has said so far
    int alphabetArray[26] = {};
    printf("Guess a letter: ");
    char letter;
    //Need to do the appropriate checkings
    //This one takes the enter character
    scanf("%c",&letter);
    scanf("%c",&letter);

    checkLetterGiven(alphabetArray,letter);

    printf("\n\n-------------------------------\n");
    gameEnd = 1;
    }

    return 0;
}
