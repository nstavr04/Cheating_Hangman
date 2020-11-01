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

int main(int argc,char *argv[]) {

    //Intro Message
    firstMessage();

    //TotalGuesses, with checking
    int totalGuesses = 0;
    printf("\nHow many total guesses?  ");
    scanf("%d",&totalGuesses);


    //Needs fixing, if you give char it goes into infinite loop
    while(totalGuesses <= 0){
        printf("Wrong number. Please insert new Total Guesses number: ");
        scanf("%d%s",&totalGuesses);
        //scanf("%d",&totalGuesses);
    }

    printf("%d",totalGuesses);

    return 0;
}
