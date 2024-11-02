#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "chess_structs.h" //allows us to use the structs we created to manage a chess game
#include "basic_ai.h" //the basic ai

int knight(int board[8][8], int ychange, int xchange, int ycoord, int xcoord) {
  if (withinBounds((ycoord + ychange), (xcoord + xchange))) {
    return board[ycoord + ychange][xcoord + xchange];
  } else {
    return -1;
  }
}

sweep_info sweep(int board[8][8], int ydir, int xdir, int ycoord, int xcoord) {
  sweep_info out;
  int run = 1;
  int i = 0;
  int color = get_color(board[ycoord][xcoord]);
  int ycheck, xcheck;
  while (run) {
    i++;
    ycheck = ycoord + i * ydir;
    xcheck = xcoord + i * xdir;
    if (withinBounds(ycheck, xcheck)) {
      if (!(board[ycheck][xcheck] == __)) {
        if (get_color(board[ycheck][xcheck]) != color) {
          out.endpiece = board[ycheck][xcheck];
          out.distance = i + 1;
        } else {
          out.endpiece = __;
          out.distance = i;
        }
        run = 0;
      }
    } else {
      out.endpiece = __;
      out.distance = i;
      run = 0;
    }
  }
  return out;
}



//check
int check(int analyze[8][8], int color) {
  int kingY;
  int kingX;
  int piece;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      piece = analyze[i][j]; // piece contains the piece we are checking

      if (color == 1) {

        // check for checks from white

        if (piece == wr || piece == wq) {
          if (sweep(analyze, -1, 0, i, j).endpiece == bk) {
            return 1;
          } // sweep down
          if (sweep(analyze, 1, 0, i, j).endpiece == bk) {
            return 1;
          } // sweep up
          if (sweep(analyze, 0, -1, i, j).endpiece == bk) {
            return 1;
          } // sweep left
          if (sweep(analyze, 0, 1, i, j).endpiece == bk) {
            return 1;
          } // sweep right
        }

        if (piece == wb || piece == wq) {
          if (sweep(analyze, 1, 1, i, j).endpiece == bk) {
            return 1;
          } // sweep up-right
          if (sweep(analyze, -1, 1, i, j).endpiece == bk) {
            return 1;
          } // sweep down-right
          if (sweep(analyze, 1, -1, i, j).endpiece == bk) {
            return 1;
          } // sweep up-left
          if (sweep(analyze, -1, -1, i, j).endpiece == bk) {
            return 1;
          } // sweep down-left
        }
        if (piece == wn) {
          if (knight(analyze, 2, 1, i, j) == bk ||
              knight(analyze, 2, -1, i, j) == bk) {
            return 1;
          }
          if (knight(analyze, -2, 1, i, j) == bk ||
              knight(analyze, -2, -1, i, j) == bk) {
            return 1;
          }
          if (knight(analyze, 1, 2, i, j) == bk ||
              knight(analyze, -1, 2, i, j) == bk) {
            return 1;
          }
          if (knight(analyze, 1, -2, i, j) == bk ||
              knight(analyze, -1, -2, i, j) == bk) {
            return 1;
          }
        }

        if (piece == wp) {
          if (withinBounds(i + 1, j - 1)) {
            if (analyze[i + 1][j - 1] == bk) {
              return 1;
            }
          }

          if (withinBounds(i + 1, j + 1)) {
            if (analyze[i + 1][j + 1] == bk) {
              return 1;
            }
          }
        }
        if (piece == wk) {
          for (int i2 = -1; i2 < 2; i2++) {
            for (int j2 = -1; j2 < 2; j2++) {
              if (withinBounds(i + i2, j + j2)) {
                if (analyze[i + i2][j + j2] == bk) {
                  return 1;
                }
              }
            }
          }
        }

      } else {

        // check for black checks
        if (piece == br || piece == bq) {
          if (sweep(analyze, -1, 0, i, j).endpiece == wk) {
            return 1;
          } // sweep down
          if (sweep(analyze, 1, 0, i, j).endpiece == wk) {
            return 1;
          } // sweep up
          if (sweep(analyze, 0, -1, i, j).endpiece == wk) {
            return 1;
          } // sweep left
          if (sweep(analyze, 0, 1, i, j).endpiece == wk) {
            return 1;
          } // sweep right
        }

        if (piece == bb || piece == bq) {
          if (sweep(analyze, 1, 1, i, j).endpiece == wk) {
            return 1;
          } // sweep up-right
          if (sweep(analyze, -1, 1, i, j).endpiece == wk) {
            return 1;
          } // sweep down-right
          if (sweep(analyze, 1, -1, i, j).endpiece == wk) {
            return 1;
          } // sweep up-left
          if (sweep(analyze, -1, -1, i, j).endpiece == wk) {
            return 1;
          } // sweep down-left
        }
        if (piece == bn) {
          if (knight(analyze, 2, 1, i, j) == wk ||
              knight(analyze, 2, -1, i, j) == wk) {
            return 1;
          }
          if (knight(analyze, -2, 1, i, j) == wk ||
              knight(analyze, -2, -1, i, j) == wk) {
            return 1;
          }
          if (knight(analyze, 1, 2, i, j) == wk ||
              knight(analyze, -1, 2, i, j) == wk) {
            return 1;
          }
          if (knight(analyze, 1, -2, i, j) == wk ||
              knight(analyze, -1, -2, i, j) == wk) {
            return 1;
          }
        }
        if (piece == bp) {
          if (withinBounds(i + 1, j - 1)) {
            if (analyze[i + 1][j - 1] == wk) {
              return 1;
            }
          }
          if (withinBounds(i + 1, j + 1)) {
            if (analyze[i + 1][j + 1] == wk) {
              return 1;
            }
          }
        }

        if (piece == bk) {
          for (int i3 = -1; i3 < 2; i3++) {
            for (int j3 = -1; j3 < 2; j3++) {
              if (withinBounds(i + i3, j + j3)) {
                if (analyze[i + i3][j + j3] == wk) {
                  return 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

int castlingRights[2] = {1,1};
amove makeMove(int board[8][8], int y1, int x1, int y2, int x2) {
  amove r;
  r.y1 = y1;
  r.x1 = x1;
  r.y2 = y2;
  r.x2 = x2;
  r.piece = board[y1][x1];
  r.enpassant = 0;
  if (r.piece == wp && y2 == 7) {
    r.piece = wq;
  }
  if (r.piece == bp && y2 == 0) {
    r.piece = bq;
  }

  if (board[y2][x2] == __) {
    r.capture = 0;
    if (r.piece % 10 == 6 && r.x2 != r.x1) {
      //en passant
      r.capture = 1;
      r.enpassant = 1;
    }
  } else {
    r.capture = 1;
  }
  
  if (abs(x2 - x1) > 1 && r.piece % 10 == 4) {
    r.castles = 1;
  } else {
    r.castles = 0;
  }

  r.color = get_color(r.piece);

  int analyze[8][8];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (i == y1 && j == x1) {
        analyze[i][j] = __; // replace previous position with blank
      } else if (i == y2 && j == x2) {
        analyze[i][j] = r.piece; // new position with piece
      } else {
        analyze[i][j] = board[i][j];
      }
    }
  }

  r.check = check(analyze, !r.color);

  if (r.capture && board[y2][x2] % 10 == 4) {
    r.y2 = r.y1;
    r.x2 = r.x1;
    r.capture = 0;
  }
  
  return r;
}

int selfCheck(int analyze[8][8], amove test) {
  int analyze2[8][8];

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (i == test.y1 && j == test.x1) {
        analyze2[i][j] = __; // replace previous position with blank
      } else if (i == test.y2 && j == test.x2) {
        analyze2[i][j] = test.piece; // new position with piece
      } else {
        analyze2[i][j] = analyze[i][j];
      }
    }
  }

  return check(analyze2, test.color);
}

void add_sweep_to_legal(movesList *dest, int board[8][8], int yc, int xc, int y,int x) {
  for (int k = 1; k < sweep(board, yc, xc, y, x).distance; k++) {
    amove test = makeMove(board, y, x, y + k * yc, x + k * xc);
    if (!selfCheck(board, test)) {
      dest->list[dest->num_moves] = test;
      dest->num_moves++;
    }
  }
}

amove last; //keep track of last move for en passant
void add_pawn_to_legal(movesList *dest, int board[8][8], int y, int x) {
  int color = get_color(board[y][x]);
  if (color == 0) {

    if (board[y + 1][x] == __) { // move 1 forward (always possible)
      amove test = makeMove(board, y, x, y + 1, x);
      if (!selfCheck(board, test)) {
        dest->list[dest->num_moves] = test;
        dest->num_moves++;
      }
      if (board[y + 2][x] == __ &&
          y == 1) { // move 2 forward (only on second rank)
        amove test = makeMove(board, y, x, y + 2, x);
        if (!selfCheck(board, test)) {
          dest->list[dest->num_moves] = test;
          dest->num_moves++;
        }
      }
    }

    // diagonal attack
    if (withinBounds(y + 1, x - 1)) {
      if (board[y + 1][x - 1] != __ && get_color(board[y + 1][x - 1]) == 1) {
        amove test = makeMove(board, y, x, y + 1, x - 1);
        if (!selfCheck(board, test)) {
          dest->list[dest->num_moves] = test;
          dest->num_moves++;
        }
      }
    }
    if (withinBounds(y + 1, x + 1)) {
      if (board[y + 1][x + 1] != __ && get_color(board[y + 1][x + 1]) == 1) {
        amove test = makeMove(board, y, x, y + 1, x + 1);
        if (!selfCheck(board, test)) {
          dest->list[dest->num_moves] = test;
          dest->num_moves++;
        }
      }
    }

    // "en passant"
      if (withinBounds(5, x + 1)) {
        if (y == 4 && board[5][x+1] == __ && board[4][x+1] == bp && last.x2 == x + 1 && last.y2 == 4 && last.y1 == 6) {
          amove test = makeMove(board, y, x, 5, x + 1);
          if (!selfCheck(board, test)) {
            dest->list[dest->num_moves] = test;
            dest->num_moves++;
          }
        }
      }
      if (withinBounds(5, x - 1)) {
        if (y == 4 && board[5][x-1] == __ && board[4][x-1] == bp && last.x2 == x - 1 && last.y2 == 4 && last.y1 == 6) {
          amove test = makeMove(board, y, x, 5, x - 1);
          if (!selfCheck(board, test)) {
            dest->list[dest->num_moves] = test;
            dest->num_moves++;
          }
        }
      }
    
  } else {
    if (board[y - 1][x] == __) { // move 1 forward (always possible)
      amove test = makeMove(board, y, x, y - 1, x);
      if (!selfCheck(board, test)) {
        dest->list[dest->num_moves] = test;
        dest->num_moves++;
      }
      if (board[y - 2][x] == __ &&
          y == 6) { // move 2 forward (only on seventh rank)
        amove test = makeMove(board, y, x, y - 2, x);
        if (!selfCheck(board, test)) {
          dest->list[dest->num_moves] = test;
          dest->num_moves++;
        }
      }
    }
    // diagonal attack
    if (withinBounds(y - 1, x - 1)) {
      if (board[y - 1][x - 1] != __ && get_color(board[y - 1][x - 1]) == 0) {
        amove test = makeMove(board, y, x, y - 1, x - 1);
        if (!selfCheck(board, test)) {
          dest->list[dest->num_moves] = test;
          dest->num_moves++;
        }
      }
    }
    if (withinBounds(y - 1, x + 1)) {
      if (board[y - 1][x + 1] != __ && get_color(board[y - 1][x + 1]) == 0) {
        amove test = makeMove(board, y, x, y - 1, x + 1);
        if (!selfCheck(board, test)) {
          dest->list[dest->num_moves] = test;
          dest->num_moves++;
        }
      }
    }

    //black enpassant
      if (withinBounds(4, x + 1)) {
        if (y == 3 && board[2][x+1] == __ && board[3][x+1] == wp && last.x2 == x + 1 && last.y2 == 3 && last.y1 == 1) {
          amove test = makeMove(board, 3, x, 2, x + 1);
          if (!selfCheck(board, test)) {
            dest->list[dest->num_moves] = test;
            dest->num_moves++;
          }
        }
      }

      if (withinBounds(4, x - 1)) {
        if (y == 3 && board[2][x-1] == __ && board[3][x-1] == wp && last.x2 == x - 1 && last.y2 == 3 && last.y1 == 1) {
          amove test = makeMove(board, 3, x, 2, x - 1);
          if (!selfCheck(board, test)) {
            dest->list[dest->num_moves] = test;
            dest->num_moves++;
          }
        }
    }
  }
}

void add_knight_to_legal(movesList *dest, int board[8][8], int y, int x) {
  int color = get_color(board[y][x]);
  int yc, xc;
  for (int i = 0; i < 8; i++) {
    if (i == 0) {
      yc = -2;
      xc = -1;
    }
    if (i == 1) {
      yc = -2;
      xc = 1;
    }
    if (i == 2) {
      yc = -1;
      xc = -2;
    }
    if (i == 3) {
      yc = -1;
      xc = 2;
    }
    if (i == 4) {
      yc = 2;
      xc = -1;
    }
    if (i == 5) {
      yc = 2;
      xc = 1;
    }
    if (i == 6) {
      yc = 1;
      xc = -2;
    }
    if (i == 7) {
      yc = 1;
      xc = 2;
    }

    if (knight(board, yc, xc, y, x) != -1 &&
        get_color(knight(board, yc, xc, y, x)) != color) {
      amove test = makeMove(board, y, x, y + yc, x + xc);
      if (!selfCheck(board, test)) {
        dest->list[dest->num_moves] = test;
        dest->num_moves++;
      }
    }
  }
}

void add_king_to_legal(movesList *dest, int board[8][8], int y, int x) {
  int color = get_color(board[y][x]);
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (!(i == 0 && j == 0)) { // king can't just stay on the same square...
        if (withinBounds(y + i, x + j)) {
          if (get_color(board[y + i][x + j]) != color) {
            amove test = makeMove(board, y, x, y + i, x + j);
            if (!selfCheck(board, test)) {
              dest->list[dest->num_moves] = test;
              dest->num_moves++;
            }
          }
        }
      }
    }
  }

  //castling white
  if (color == 0 && castlingRights[0] && board[0][5] == __ &&
    board[0][6] == __ && board[0][7] == wr) {
    amove test = makeMove(board, y, x, y, x+2);
    if (!selfCheck(board, test)) {
      dest->list[dest->num_moves] = test;
      dest->num_moves++;
    }
  }
  if (color == 0 && castlingRights[0] && board[0][3] == __ &&
    board[0][2] == __ && board[0][1] == __ && board[0][0] == wr) {
    amove test = makeMove(board, y, x, y, x-2);
    if (!selfCheck(board, test)) {
      dest->list[dest->num_moves] = test;
      dest->num_moves++;
    }
  }

  //castling black
  if (color == 1 && castlingRights[1] && board[7][5] == __ &&
    board[7][6] == __ && board[7][7] == br) {
    amove test = makeMove(board, y, x, y, x+2);
    if (!selfCheck(board, test)) {
      dest->list[dest->num_moves] = test;
      dest->num_moves++;
    }
  }
  if (color == 1 && castlingRights[1] && board[7][3] == __ &&
    board[7][2] == __ && board[7][1] == __ && board[7][0] == br) {
    amove test = makeMove(board, y, x, y, x-2);
    if (!selfCheck(board, test)) {
      dest->list[dest->num_moves] = test;
      dest->num_moves++;
    }
  }
}

// LEGAL MOVES LIST //
movesList getLegalMoves(int board[8][8], int color) {

  // initialize return list
  movesList lm;
  lm.num_moves = 0;

  // Cycle through every space on the board
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int piece = board[i][j]; // This is the current piece

      if (get_color(piece) == color) {
        if (piece % 10 == 1 || piece % 10 == 5) { // ROOK or QUEEN
          add_sweep_to_legal(&lm, board, 1, 0, i, j);
          add_sweep_to_legal(&lm, board, -1, 0, i, j);
          add_sweep_to_legal(&lm, board, 0, 1, i, j);
          add_sweep_to_legal(&lm, board, 0, -1, i, j);
        }
        if (piece % 10 == 3 || piece % 10 == 5) { // BISHOP or QUEEN
          add_sweep_to_legal(&lm, board, 1, 1, i, j);
          add_sweep_to_legal(&lm, board, 1, -1, i, j);
          add_sweep_to_legal(&lm, board, -1, 1, i, j);
          add_sweep_to_legal(&lm, board, -1, -1, i, j);
        }
        if (piece % 10 == 6) { // PAWN
          add_pawn_to_legal(&lm, board, i, j);
        }

        if (piece % 10 == 2) { // KNIGHT
          add_knight_to_legal(&lm, board, i, j);
        }

        if (piece % 10 == 4) { // KING
          add_king_to_legal(&lm, board, i, j);
        }
      }
    }
  }
  return lm;
}

int stalemate = -1;
int checkmate(int analyze[8][8], int color) {
  stalemate = -1;
  int legal = getLegalMoves(analyze, color).num_moves;
  if (legal == 0) {
    if (check(analyze, color)) {
      return 1;
    } else {
      stalemate = color;
      return 0;
    }
  } else {
    return 0;
  }
}

int moves_without_capture;
void updateBoard(int board[8][8], amove todo) {
  last = todo;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (i == todo.y1 && j == todo.x1) {
        board[i][j] = __;
      } else if (i == todo.y2 && j == todo.x2) {
        board[i][j] = todo.piece;
      }
    }
  }
  if (todo.castles && todo.color == 0) {
    if (todo.x2 == 6) {
      board[0][7] = __;
      board[0][5] = wr;
    } else {
      board[0][0] = __;
      board[0][3] = wr;
    }
  }
  if (todo.castles && todo.color == 1) {
    if (todo.x2 == 6) {
      board[7][7] = __;
      board[7][5] = br;
    } else {
      board[7][0] = __;
      board[7][3] = br;
    }
  }

  if  (todo.enpassant) {
    board[todo.y1][todo.x2] = __;
  }
  
  if (todo.piece == wk) {
    castlingRights[0] = 0;
  }
  if (todo.piece == bk) {
    castlingRights[1] = 0;
  }

  if (todo.capture || todo.piece % 10 == 6) {
    moves_without_capture = 0;
  } else {
    moves_without_capture++;
  }
}

void printPiece(int piece) {
  if (piece == __) {
    printw(" ");
  }
  if (piece == wk) {
    printw("%lc", L'\u2654');
  }
  if (piece == wq) {
    printw("%lc", L'\u2655');
  }
  if (piece == wr) {
    printw("%lc", L'\u2656');
  }
  if (piece == wb) {
    printw("%lc", L'\u2657');
  }
  if (piece == wn) {
    printw("%lc", L'\u2658');
  }
  if (piece == wp) {
    printw("%lc", L'\u2659');
  }

  if (piece == __) {
    printw(" ");
  }
  if (piece == bk) {
    printw("%lc", L'\u265A');
  }
  if (piece == bq) {
    printw("%lc", L'\u265B');
  }
  if (piece == br) {
    printw("%lc", L'\u265C');
  }
  if (piece == bb) {
    printw("%lc", L'\u265D');
  }
  if (piece == bn) {
    printw("%lc", L'\u265E');
  }
  if (piece == bp) {
    printw("%lc", L'\u265F');
  }
}


void printBoard(int board[8][8], int cursorY, int cursorX, int highlights[25][2], int theme) {
  // clear();
  int bg = 0;

  // Gold and White theme 1 AKA Frozen
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_BLACK, COLOR_BLUE);
  init_pair(4, COLOR_BLACK, COLOR_BLUE);

  // Highlight squares
  init_pair(5, COLOR_BLACK, COLOR_BLACK);
  init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(17, COLOR_BLACK, COLOR_RED);
  init_pair(23, COLOR_BLACK, COLOR_YELLOW);
  init_pair(24, COLOR_BLACK, COLOR_CYAN);

  // Gold and White theme 1 AKA Oppenheimer
  init_pair(7, COLOR_BLACK, COLOR_WHITE);
  init_pair(8, COLOR_BLACK, COLOR_WHITE);
  init_pair(9, COLOR_BLACK, COLOR_YELLOW);
  init_pair(10, COLOR_BLACK, COLOR_YELLOW);

  // Pink and White theme 2 AKA Barbie
  init_pair(13, COLOR_BLACK, COLOR_WHITE);
  init_pair(14, COLOR_BLACK, COLOR_WHITE);
  init_pair(15, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(16, COLOR_BLACK, COLOR_MAGENTA);

  // Black and White theme 3 AKA Traditional or Trash
  init_pair(19, COLOR_BLACK, COLOR_WHITE);
  init_pair(20, COLOR_BLACK, COLOR_WHITE);
  init_pair(21, COLOR_BLACK, COLOR_BLACK);
  init_pair(22, COLOR_BLACK, COLOR_BLACK);

  for (int i = 7; i >= 0; i--) {
    for (int j = 0; j < 8; j++) {
      if (bg == 1) {
        bg = 0;
        if (get_color(board[i][j]) == 0) {
          attron(COLOR_PAIR(1 + (theme * 6)));
        } else {
          attron(COLOR_PAIR(2 + (theme * 6)));
        }
      } else {
        bg = 1;
        if (get_color(board[i][j]) == 0) {
          attron(COLOR_PAIR(3 + (theme * 6)));
        } else {
          attron(COLOR_PAIR(4 + (theme * 6)));
        }
      }

      // HIGHLIGHT SQUARE YOU CAN GO TO
      for (int index = 0; index < 25; index++) {
        if (highlights[index][0] == i && highlights[index][1] == j) {
          if (theme == 2) {
            attron(COLOR_PAIR(3));
          } else if (theme == 3) {
            attron(COLOR_PAIR(24));
          } else {
            attron(COLOR_PAIR(6));
          }
        }
      }

      // HIGHLIGHT THE CURSOR

      if (i == cursorY && j == cursorX) {
        if (theme == 3) {
          attron(COLOR_PAIR(23));
        } else {
          attron(COLOR_PAIR(5));
        }
      }

      move(7 - i, j * 2);
      printPiece(board[i][j]);
      move(7 - i, j * 2 + 1);
      printw(" ");
    }
    if (bg == 1) {
      bg = 0;
    } else {
      bg = 1;
    }
  }
}

movesList getMovesFromCoord(movesList allMoves, int y, int x) {
  // takes in list of legal moves and returns a list of legal moves from a 
  // certain piece (so you can highlight all moves a certain piece can make)
  movesList r;
  r.num_moves = 0;
  for (int i = 0; i < allMoves.num_moves; i++) {

    if (allMoves.list[i].y1 == y && allMoves.list[i].x1 == x) {
      r.list[r.num_moves] = allMoves.list[i];
      r.num_moves++;
    }
  }
  return r;
}

int input = 0;
int cursorY = 0;
int cursorX = 0;

void moveCursor() {
  input = getch();
  if (input == KEY_UP && cursorY < 7) {
    cursorY++;
  }
  if (input == KEY_DOWN && cursorY > 0) {
    cursorY--;
  }
  if (input == KEY_LEFT && cursorX > 0) {
    cursorX--;
  }
  if (input == KEY_RIGHT && cursorX < 7) {
    cursorX++;
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  // choose theme, number of human players
  int theme;
  int humans = 1;
  int white_difficulty = 0;
  int black_difficulty = 1;
  if (argc > 1) {
    theme = atoi(argv[1]);
  } else {
    theme = 0;
  }
  if (argc > 2) {
    humans = atoi(argv[2]);
  }
  if (argc > 3) {
    if (humans == 0) {
      white_difficulty = atoi(argv[3]);
      if (argc > 4) {
        black_difficulty = atoi(argv[4]);
      }
    } else {
      black_difficulty = atoi(argv[3]);
    }
  }

  //include necessary ncurses things
  setlocale(LC_ALL, "");
  initscr(); /* Start curses mode */
  start_color();
  cbreak();
  halfdelay(2);
  typeahead(-1);
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  //set up the board
  int board[8][8] = {
      {wr, wn, wb, wq, wk, wb, wn, wr}, 
      {wp, wp, wp, wp, wp, wp, wp, wp},
      {__, __, __, __, __, __, __, __}, 
      {__, __, __, __, __, __, __, __},
      {__, __, __, __, __, __, __, __}, 
      {__, __, __, __, __, __, __, __},
      {bp, bp, bp, bp, bp, bp, bp, bp}, 
      {br, bn, bb, bq, bk, bb, bn, br}};

  // reset the highlights list
  int highlights[25][2];
  for (int i = 0; i < 25; i++) {
    highlights[i][0] = -1;
    highlights[i][1] = -1;
  }

  movesList l;
  movesList m;

  int turn = 0;
  int toPrint;

  //main gameplay loop
  while (1) {

    //print board and get legal moves
    printBoard(board, cursorY, cursorX, highlights, theme);
    l = getLegalMoves(board, 0);
    m = getLegalMoves(board, 1);
    toPrint = 0;

    //toPrint lowers the amount of time printing
    while (toPrint == 0) {
      //White's Turn
      if (turn == 0) {

        if (humans == 0) {
          //White as an AI
          getch();
          amove choice;

          //ai difficulty
          if (!white_difficulty) {
            choice = l.list[rand() % l.num_moves];
          } else {
            choice = myAi(board, l);
          }
          
          updateBoard(board, choice);
          toPrint = 1;
          turn = 1;
        } else {
          //White as a human player
          toPrint = 1;
          moveCursor();

          if (input == 32) {
            clear();
            // are you moving a piece (eg selecting a highlighted square)
            int cursorMode = 0;
            for (int i = 1; i < 25; i++) {
              if (highlights[i][0] == cursorY && highlights[i][1] == cursorX) {
                cursorMode = 1;
                break;
              }
            }

            // if you aren't...
            if (cursorMode == 0) { // select new square mode
              for (int i = 0; i < 25; i++) {
                highlights[i][0] = -1;
                highlights[i][1] = -1;
              }
              highlights[0][0] = cursorY;
              highlights[0][1] = cursorX; // highlight selected piece

              movesList selectedMoves = getMovesFromCoord(l, cursorY, cursorX);
              for (int i = 0; i < selectedMoves.num_moves; i++) {
                highlights[i + 1][0] = selectedMoves.list[i].y2;
                highlights[i + 1][1] = selectedMoves.list[i].x2;
              }

            } else {
              for (int i = 0; i < l.num_moves; i++) {
                if (l.list[i].y1 == highlights[0][0] &&
                    l.list[i].x1 == highlights[0][1] &&
                    l.list[i].y2 == cursorY && l.list[i].x2 == cursorX) {
                  updateBoard(board, l.list[i]);
                  break;
                }
              }
              for (int i = 0; i < 25; i++) {
                highlights[i][0] = -1;
                highlights[i][1] = -1;
                turn = 1;
                toPrint = 1;
              }
            }
          }
        }

      } else {

        //Black's Turn

        if (humans == 2) {
          //Black as a human player

          toPrint = 1;
          moveCursor();

          if (input == 32) {
            clear();
            // are you moving a piece (eg selecting a highlighted square)
            int cursorMode = 0;
            for (int i = 1; i < 25; i++) {
              if (highlights[i][0] == cursorY && highlights[i][1] == cursorX) {
                cursorMode = 1;
                break;
              }
            }

            // if you aren't...
            if (cursorMode == 0) { // select new square mode
              for (int i = 0; i < 25; i++) {
                highlights[i][0] = -1;
                highlights[i][1] = -1;
              }
              highlights[0][0] = cursorY;
              highlights[0][1] = cursorX; // highlight selected piece

              movesList selectedMoves = getMovesFromCoord(m, cursorY, cursorX);
              for (int i = 0; i < selectedMoves.num_moves; i++) {
                highlights[i + 1][0] = selectedMoves.list[i].y2;
                highlights[i + 1][1] = selectedMoves.list[i].x2;
              }

            } else {
              for (int i = 0; i < l.num_moves; i++) {
                if (m.list[i].y1 == highlights[0][0] &&
                    m.list[i].x1 == highlights[0][1] &&
                    m.list[i].y2 == cursorY && m.list[i].x2 == cursorX) {
                  updateBoard(board, m.list[i]);
                  break;
                }
              }
              for (int i = 0; i < 25; i++) {
                highlights[i][0] = -1;
                highlights[i][1] = -1;
                turn = 0;
                toPrint = 1;
              }
            }
          }
        } else {
          //Black as an AI
          amove choice;
          if (!black_difficulty) {
            choice = m.list[rand() % m.num_moves];
          } else {
            choice = myAi(board, m);
          }
          updateBoard(board, choice);
          toPrint = 1;
          turn = 0;
        }
      }
    }

    // is it checkmate?
    if (checkmate(board, 1)) {
      for (int i = 0; i < 25; i++) {
        highlights[i][0] = 100;
        highlights[i][1] = 100;
      }
      clear();
      move(0, 18);
      printw("CHECKMATE, WHITE WINS");
      printBoard(board, 100, 100, highlights, theme);
      getch();
      return 0;
    }

    if (checkmate(board, 0)) {
      for (int i = 0; i < 25; i++) {
        highlights[i][0] = 100;
        highlights[i][1] = 100;
      }
      clear();
      move(0, 18);
      printw("CHECKMATE, BLACK WINS");
      printBoard(board, 100, 100, highlights, theme);
      getch();
      return 0;
    }

    if (moves_without_capture > 49 || stalemate == turn) {
      for (int i = 0; i < 25; i++) {
        highlights[i][0] = 100;
        highlights[i][1] = 100;
      }
      clear();
      move(0, 18);
      printw("STALEMATE");
      printBoard(board, 100, 100, highlights, theme);
      getch();

      endwin();
      return 0;
    }
  }

  endwin();
  return 0;
}
