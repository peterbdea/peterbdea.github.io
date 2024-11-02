#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "chess_structs.h"

amove myAi(int board[8][8], movesList moves) {
  amove choice;
  int color = moves.list[0].color;

  if (color) {
    int far = 8;
    // If all else fails, push a piece as far as it can
    // into enemy territory
    for (int i = 0; i < moves.num_moves; i++) {
      if (moves.list[i].y2 < far) {
        far = moves.list[i].y2;
        choice = moves.list[i];
      }
    }
  } else {
    int far = 0;
    // If all else fails, push a piece as far as it can
    // into enemy territory
    for (int i = 0; i < moves.num_moves; i++) {
      if (moves.list[i].y2 > far) {
        far = moves.list[i].y2;
        choice = moves.list[i];
      }
    }
  }
  
  // Second priority is to put the enemy king in check
  for (int i = 0; i < moves.num_moves; i++) {
    if (moves.list[i].check) {
      choice = moves.list[i];
    }
  }
  // First priority is to capture a piece if able
  for (int i = 0; i < moves.num_moves; i++) {
    if (moves.list[i].capture) {
      choice = moves.list[i];
    }
  }
  return choice;
}
