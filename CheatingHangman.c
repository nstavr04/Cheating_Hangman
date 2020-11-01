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

int main(int argc,char *argv[]) {

    //Intro Message
    firstMessage();

    //Give the number of guesses
    int totalGuesses = giveGuessTries();

    printf("%d\n",totalGuesses);

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

    printf("%s",wordProgress);

    while(1==1){



    }

    return 0;
}
