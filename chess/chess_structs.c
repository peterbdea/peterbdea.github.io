#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// blank tile
#define __ 0
// assign each white piece an int
#define wr 11
#define wn 12
#define wb 13
#define wk 14
#define wq 15
#define wp 16
// assign each black piece an int
#define br 21
#define bn 22
#define bb 23
#define bk 24
#define bq 25
#define bp 26

typedef struct amove {
  int y1;
  int x1;
  int y2;
  int x2;
  int color;
  int check;
  int checkmate;
  int capture;
  int castles;
  int piece;
} amove;

typedef struct movesList {
  amove list[256];
  int num_moves;
} movesList;

typedef struct sweep_info {
  int distance;
  int endpiece;
} sweep_info;

int get_color(int piece) {
  // input piece and return color (0 for white, 1 for black)
  if (piece > 20) {
    return 1;
  } else if (piece < 20 && piece > 0) {
    return 0;
  } else {
    return -1;
  }
}

int withinBounds(int row, int col) {
  if (row > -1 && row < 8 && col > -1 && col < 8) {
    return 1;
  } else {
    return 0;
  }
}


