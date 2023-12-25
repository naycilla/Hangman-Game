#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "hangman.h"
#include <time.h>

typedef struct {
    char *category;
    char *words[6]; // every category has 6 word
} category;



// generate random num in range 0-5
int rndm(){
	int w = rand()%6;
	return w;
}	


// sort word by length
void bblsort(char *arr[], int n) {
	int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strlen(arr[j]) > strlen(arr[j + 1])) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void readWordsFromFile(char *filename, char *words[]) {
	
	int i;
    FILE *file = fopen(filename, "r"); // open and reads file
    
    // exit if file isn't exist
    if (file == NULL) {
        printf("Can not open file");
        exit(1);
    }

	// read 6 words for every category
    for (i = 0; i < 6; i++) {
        char word[30]; 
        if (fgets(word, sizeof(word), file) != NULL) {
            word[strcspn(word, "\n")] = '\0'; // remove newline character
            words[i] = strdup(word);
        } else {
            // handle end of file or error
            if (feof(file)) {
                break;
            } else {
                perror("Error reading from file");
                exit(EXIT_FAILURE);
            }
        }
    }	

    fclose(file);
}

int main(){
	
	unsigned int attemp=0, found=0, allGuessed=1, cat;
	char *secretWord, *guessedWord;
    char guessedLetters[26] = {0}; // a-z
    char guess;

	category ctgry[4]; 

    ctgry[0].category = ""; 
    ctgry[1].category = "fruits";
    ctgry[2].category = "animals";
    ctgry[3].category = "jobs";
    

    readWordsFromFile("fruits.txt", ctgry[1].words);
    readWordsFromFile("animals.txt", ctgry[2].words);
    readWordsFromFile("jobs.txt", ctgry[3].words);
    
	int n;
	
    // sort the words based on length
    for (n = 1; n <= 3; n++) {
        bblsort(ctgry[n].words, 6);
    }
	
	
//	generate different random int when program excecuted
	srand(time(NULL));
	
	
//	print list category
	printf("--- CATEGORY ---\n");
	printf("1. Fruits\n");
	printf("2. Animals\n");
	printf("3. Jobs\n");
	
	
//	scan category 
	do{
		
		printf("\nSelect Category : ");
		scanf("%d", &cat); 
		
	} while(cat<1 || cat>3); // asking input if user input wrong category
	
	clrscr();
	
//	get random word from choosen category
	secretWord = ctgry[cat].words[rndm()];

	
//	turn word into underscores ( "apple"  =>  "_ _ _ _ _" )
    guessedWord = (char *)malloc(2 * strlen(secretWord) + 1);	// allocate memory for guessed word + spasi
    
    int i, j = 0;
    for (i = 0; i < strlen(secretWord); i++) {

			guessedWord[j++] = '_';  // replace char with '_'
		    if (i < strlen(secretWord) - 1) {
		        guessedWord[j++] = ' ';  // add space after '_' , except last char
		    }
        
    }
    
    guessedWord[j] = '\0';  // end of string
//

	while (attemp <= 6) {
		
        clrscr();
        

//      print hangman pic
        hngmn(attemp);

//		print word that has to be guessed ( "apple" => "_ _ _ _ _" )
        printf("\n%s\n", guessedWord);

        // print guessedLetters if exist
        printf("\nGuessed Letters: ");
        if(guessedLetters[0] != '\0'){
        	for (i = 0; i < strlen(guessedLetters); i++) {
	            printf("%c ", guessedLetters[i]);
	        } 
		} else printf(" ");

        printf("\nGuess a letter : ");
        scanf(" %c", &guess);			// scan letter
		guess = tolower(guess);			// change letter into lowercase
		
        // check if the letter has been guessed
		if (strchr(guessedLetters, guess) != NULL) {
		    printf("You already guessed that letter.\n");
		    continue;
		}
		
		
		// add the guessed letter to the list
		guessedLetters[strlen(guessedLetters)] = guess;
		guessedLetters[strlen(guessedLetters) + 1] = '\0';
		
		found = 0; 
		
		
		// search guessed letter in the secretWord
		for (i = 0; i < strlen(secretWord); i++) {
		    if (secretWord[i] == guess) {
		        guessedWord[i*2] = guess;
		        found = 1; 	// guessed letter exist
		    }
		}
		
		
		// check if the player has guessed all the letters
		int allGuessed = 1;
		for (i = 0; i < strlen(secretWord); i++) {
		    if (secretWord[i] != ' ' && guessedWord[i * 2] != secretWord[i]) {
		        allGuessed = 0;
		        break;
		    }
		}
		
		if (allGuessed == 1) {
		    clrscr();
		    hngmn(attemp);
		    printf("\n%s\n", guessedWord);
		    printf("\nCongrats! You guessed the word: %s\n", secretWord);
		    break;
		}
		
	
		// check if user guessed wrong
		if(found == 0) {
		    attemp++;
		
		    // check if the player has no attempts left
		    if(attemp == 6) {
		        clrscr();
		        hngmn(attemp);
		        printf("\n%s\n", guessedWord);
		        printf("\nSorry, you ran out of attempts. The correct word was: %s\n", secretWord);
		        break;
		    }
		}
		
    }
    
    
    free(guessedWord); // free allocated memory in guessedWord
    
	return 0;
}


