#include <stdio.h>
#include <string.h>

#define WORD_LENGTH 5
#define MAX_GUESSES 6


void toLowerCase(char str[]);
void getGuess(char guess[]);
int isValidGuess(char guess[]);
void printGuesses(char guesses[][WORD_LENGTH + 1], char resultMarks[][WORD_LENGTH + 1], int guessCount);
void markGuess(char guess[], char secret[], char result[]);
void loadWord(char word[]);
char toUpper(char c);

int main() {
    char secret[WORD_LENGTH + 1];
    loadWord(secret);

    char guesses[MAX_GUESSES][WORD_LENGTH + 1];
    char marks[MAX_GUESSES][WORD_LENGTH + 1];
    int guessCount = 0;

    while (guessCount < MAX_GUESSES) {
        char guess[WORD_LENGTH + 1];

        getGuess(guess);
        toLowerCase(guess);

        markGuess(guess, secret, marks[guessCount]);

        for (int i = 0; i < WORD_LENGTH; i++) {
            guesses[guessCount][i] = (guess[i] == secret[i]) ? toUpper(guess[i]) : guess[i];
        }
        guesses[guessCount][WORD_LENGTH] = '\0';

        printGuesses(guesses, marks, guessCount + 1);

        int correct = 1;
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (guess[i] != secret[i]) {
                correct = 0;
                break;
            }
        }

        if (correct) {
            printf("You won in %d guesses!\nNice!\n", guessCount + 1);
            return 0;
        }

        guessCount++;
    }

    printf("You lost, better luck next time!\n");
    return 0;
}


void loadWord(char word[]) {
    char temp[] = "squab";
    for (int i = 0; i < WORD_LENGTH; i++) {
        word[i] = temp[i];
    }
    word[WORD_LENGTH] = '\0';
}


char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}


void toLowerCase(char str[]) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
}


void getGuess(char guess[]) {
    while (1) {
        printf("Enter your guess: ");
        scanf("%5s", guess); 

        if (isValidGuess(guess)) break;

        printf("Your guess must be 5 letters long and contain only letters.\nPlease try again.\n");
    }
}


int isValidGuess(char guess[]) {
    int i = 0;
    while (guess[i] != '\0') {
        char c = guess[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
            return 0;
        i++;
    }
    return i == WORD_LENGTH;
}


void printGuesses(char guesses[][WORD_LENGTH + 1], char resultMarks[][WORD_LENGTH + 1], int guessCount) {
    printf("================================\n");
    for (int i = 0; i < guessCount; i++) {
        printf("%s\n", guesses[i]);
        printf("%s\n", resultMarks[i]);
    }
}


void markGuess(char guess[], char secret[], char result[]) {
    int matched[WORD_LENGTH] = {0};

   
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == secret[i]) {
            result[i] = ' ';
            matched[i] = 1;
        } else {
            result[i] = ' ';
        }
    }

    
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] != secret[i]) {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!matched[j] && guess[i] == secret[j] && guess[j] != secret[j]) {
                    result[i] = '^';
                    matched[j] = 1;
                    break;
                }
            }
        }
    }

    result[WORD_LENGTH] = '\0';
}

