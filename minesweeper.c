//This is a playable version of minesweeper in the console


#include<stdio.h>
#include<stdlib.h>
#include <time.h>



int main(void) {
  srand(time(0));
  printf("Welcome to minesweeper.\nTo play, type in the coordinates of "
         "an area you think is safe.\nYour guesses should be in the form of "
         "capital letter, space, number.\nExample: 'A 1'.\nIf you would like to place a flag, start by saying 'X 0', then choose a spot for your flag.\n\n");
  int lose = 0;
  int sx = 5;
  int sy = 5;
  int mines[sy][sx]; // make board
  int nums[sy][sx];
  for (int y = 0; y < sy; y++) {
    for (int x = 0; x < sx; x++) {
      nums[y][x] = 9;
      mines[y][x] = 0;
    }
  }

  int num_mines = 5;
  for (int i = 0; i < num_mines; i++) {
    mines[rand() % sy][rand() % sx] = 1; // make mines
  }

//   printf("\n\n");
//   // cheatC
//   printf("  ");
//   for (int x = 0; x < sx; x++) {
//     printf("%c", (char)(x + 65));
//   }
//   for (int y = 0; y < sy; y++) {
//     printf("\n %d ", y); // Print numbers
//     for (int x = 0; x < sx; x++) {
//       printf("%d", mines[y][x]);
//     }
//   }
//   printf("\n\n");

  while (!lose) {
    printf("     ");
    for (int x = 0; x < sx; x++) {
      printf("%c ", (char)(x + 65));
    } // Print Letters
    for (int y = 0; y < sy; y++) {
      printf("\n %2d |", y); // Print numbers
      for (int x = 0; x < sx; x++) {

        if (nums[y][x] == 9) {
          printf(".");
        } else if (nums[y][x] == 10) {
          printf("F");
        } else  if (nums[y][x] == 0) {
          printf(" ");
        } else {
          printf("%d", nums[y][x]);
        }
        printf("|");
        //^^Print clues
      }
      for (int i = 0; i < sx; i++){
        // printf("---");
      }
    }
    char letter;
    int number;
    int number2;
    int flag = 0;

    printf("\n\nEnter coordinates: ");
    scanf("%s %d", &letter, &number);
    number2 = (int)(letter)-65;

    if (letter == 'X'){
      flag = 1;
      printf("\n\nWhere would you like to place the flag?\n");
      scanf("%s %d", &letter, &number);
      number2 = (int)(letter)-65;
    }
    

    if (!flag) {
      if (mines[number][number2]) {
        lose = 1;
      }

      int neighbors = 0;
      if (number != 0) {
        if (number2 != 0 && mines[number - 1][number2 - 1]) {
          neighbors++;
        }
        if (mines[number - 1][number2]) {
          neighbors++;
        }
        if (number2 != sx - 1 && mines[number - 1][number2 + 1]) {
          neighbors++;
        }
      }

      if (number2 != 0 && mines[number][number2 - 1]) {
        neighbors++;
      }
      if (number2 != sx - 1 && mines[number][number2 + 1]) {
        neighbors++;
      }

      if (number != sy - 1) {
        if (number2 != 0 && mines[number + 1][number2 - 1]) {
          neighbors++;
        }
        if (mines[number + 1][number2]) {
          neighbors++;
        }
        if (number2 != sx - 1 && mines[number + 1][number2 + 1]) {
          neighbors++;
        }
      }

      nums[number][number2] = neighbors;
      
    } else {
      nums[number][number2] = 10;
    }
    int blanks = 0;
    for (int y = 0; y < sy; y++){
      for (int x = 0; x < sx; x++){
        if (nums[y][x] == 9 && !mines[y][x]){
          blanks++;
        }
      }
    }
    if (blanks == 0){
      lose = 2;
    }
  }

  if (lose== 1){
    printf("\nGAME OVER");
  } else {
    printf("\nYOU WIN!");
  }
  printf("\n\n");

  //PRINT BOARD WITH MINES

  printf("    ");
    for (int x = 0; x < sx; x++) {
      printf("%c ", (char)(x + 65));
    } // Print Letters
    for (int y = 0; y < sy; y++) {
      printf("\n %d |", y); // Print numbers
      for (int x = 0; x < sx; x++) {
        if (mines[y][x]) {
          printf("X|");
        } else{
          printf(".|");
        }
      }
      for (int i = 0; i < sx; i++){
        // printf("---");
      }
    }
  
}
