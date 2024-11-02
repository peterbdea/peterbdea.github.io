#ifndef CHESS_STRUCTS_H
#define CHESS_STRUCTS_H

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
  int enpassant;
} amove;

typedef struct movesList {
  amove list[256];
  int num_moves;
} movesList;

typedef struct sweep_info {
  int distance;
  int endpiece;
} sweep_info;

//returns the color of a piece
int get_color(int piece);

//returns whether given indices are within an 8x8 grid
int withinBounds(int row, int col);

#endif
