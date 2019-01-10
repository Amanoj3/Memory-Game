#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define half_deck 26 // to keep the game short, I chose a half deck as opposed to 52 cards

// the struct below defines the necessary attributes of each card

struct card_Info {
    char card_ID; //corresponds to an index of cardArrat
    int is_Gone; //is it present or not?
    char* cardStr; //user input like A1, A2, a.k.a the "coordinates" of the game board
};

char cardArray[half_deck] = {'1','1','2','2','3','3','4','4','5','5','6','6','7','7','8','8','9','9','T','T','J','J','Q','Q','K','K'};
char cardArray_covered[half_deck] = {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'};
int cardPairs = 13;

void swap(char* a, char*b) { //this is called in the shuffle function below
    char temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(char arr[],int n) { // credits to geeksforgeeks for this function

    int i;
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );

    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);

        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}

int validInput(char* str) { // checks if user input is valid

  if (strlen(str) != 2) { // is the size 2?
      printf("Nope.\n");
      return 0;
  }

  if ((str[0]=='A' && str[1] =='1')|| (str[0]=='A' && str[1] == '6')
  || (str[0] == 'E' && str[1] == '1') || (str[0] == 'E' && str[1] == '6')) {
      printf("Nope.\n");
      return 0;
  } // is it out of bounds?

  if ((str[0] >= 'A' && str[0] <= 'E') && (str[1] >= '1' && str[1] <='6')) {
      printf("Valid.\n");
      return 1; // if it is within the board, then return 1
  }

  else {
      printf("Not valid.\n");
      return 0;
  }
}

void displayBoardCovered() { // displays the cards that are "facing down"
   int x;
   int counter = 0;
   int numbering = 3;

   printf("    A    B    C    D    E   \n");
   printf("  =======================\n");
   printf("1");
   printf("        %c    %c    %c",cardArray_covered[0],cardArray_covered[1],cardArray_covered[2]);
   printf("\n");
   printf("2");
   for (x = 3; x <23; x++) {
       printf("   %c ",cardArray_covered[x]);
       counter++;
       if (counter % 5 == 0) {
           printf("\n");
           printf("%d",numbering);
           numbering++;
       }
   }
   printf("        %c    %c    %c", cardArray_covered[23],cardArray_covered[24],cardArray_covered[25]);
   printf("\n");
   printf("  =======================\n");
}

int main() {

    shuffle(cardArray,half_deck); // shuffles the cards randomly
    // for testing purposes, I would comment this line out so I would know where the cards are

    int i,j,k, toStore, toStore2, matchMode;
    char userInput[20];
    char userInput2[20];

    //initialize an array of the type card_Info

    struct card_Info cards[half_deck];

    for (i = 0; i<half_deck; i++) {
        cards[i].card_ID = cardArray[i];
        cards[i].is_Gone = 0;
    }

    // assign a card to a particular "coordinate"
    cards[0].cardStr = "B1";
    cards[1].cardStr = "C1";
    cards[2].cardStr = "D1";
    cards[3].cardStr = "A2";
    cards[4].cardStr = "B2";
    cards[5].cardStr = "C2";
    cards[6].cardStr = "D2";
    cards[7].cardStr = "E2";
    cards[8].cardStr = "A3";
    cards[9].cardStr = "B3";
    cards[10].cardStr = "C3";
    cards[11].cardStr = "D3";
    cards[12].cardStr = "E3";
    cards[13].cardStr = "A4";
    cards[14].cardStr = "B4";
    cards[15].cardStr = "C4";
    cards[16].cardStr = "D4";
    cards[17].cardStr = "E4";
    cards[18].cardStr = "A5";
    cards[19].cardStr = "B5";
    cards[20].cardStr = "C5";
    cards[21].cardStr = "D5";
    cards[22].cardStr = "E5";
    cards[23].cardStr = "B6";
    cards[24].cardStr = "C6";
    cards[25].cardStr = "D6";

    while (cardPairs >0) {

        displayBoardCovered();
        printf("Enter column and row:\n");
        scanf("%s", &userInput);
        if (userInput[0] == 'x' || userInput[0] == 'X') {
            printf("Exiting game now..\n");
            return 0;
        }
        userInput[0] = toupper(userInput[0]);

        if (validInput(userInput)) {
            for (k = 0; k < half_deck; k++) {
               if (strcmp(userInput,cards[k].cardStr) == 0) { // the loop is used so we can obtain the index k
                   toStore = k;
                   break; // now we obtained the index of the card, we can break
               }
            }

            if (cards[toStore].is_Gone == 1) {
                printf("The card is already gone. Try again.\n");
                continue;
            }

            printf("Now, select the second card:\n");
            scanf("%s",userInput2);

            userInput2[0] = toupper(userInput2[0]);

            if (userInput2[0] == 'x' || userInput2[0] == 'X') {
                printf("Exiting game now..\n");
                return 0;
            }


            if (strcmp(userInput,userInput2) == 0) {
                printf("The second card is the same one as the first. Try again!\n");
                continue;
            }

            if (validInput(userInput2)) {
               for (j = 0; j<half_deck;j++) {
                 if (strcmp(userInput2,cards[j].cardStr) == 0) {
                     toStore2 = j;
                     break;
                 }
               }

               if (cards[toStore2].is_Gone == 1) {
                   printf("The second card you picked is also gone. Try again.\n");
                   continue;
               }

               if ((cards[toStore].card_ID) == (cards[toStore2].card_ID)) {
                   printf("There is a match!\n");
                   printf("\n The cards were %c and %c.\n",cards[toStore].card_ID, cards[toStore2].card_ID);
                   matchMode = 1;
                   if (matchMode == 1) {
                     cardArray_covered[toStore] = ' ';  // if there is a match, remove the cards
                     cardArray_covered[toStore2] = ' ';
                     cards[toStore].is_Gone = 1; // the cards are now gone since they were indeed matched
                     cards[toStore2].is_Gone = 1;
                     cardPairs = cardPairs - 1; //fewer pairs of cards are remaining
                     matchMode = 0; // turn off the flag since we will need to determine more matches afterwards
                   }
                   //return 0;
               }

               else if ((cards[toStore].card_ID) != (cards[toStore2].card_ID)) {
                 printf("The two cards do not match. Try again.\n");
               }

            }

            else if (!(validInput(userInput2))) {
                printf("The SECOND card is not valid. Try again.\n");
            }

        }

        else if (!(validInput(userInput))) {
            printf("The first card is not valid. Try again.\n");
        }
    }

    printf("No more pairs remaining.. You finished the game. Congratulations!\n");
    displayBoardCovered();
    return 0;
}
