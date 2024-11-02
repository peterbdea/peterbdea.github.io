How to Play!
- To start the chess game, from the shell terminal enter ./main numboard numplayer ai_skill_level ai_skill_level
- For numboard enter either 0, 1 or 2, this is to select your board design
- 0 is called Frozen
- 1 is called Oppenheimer
- 2 is called Barbie
- 3 is called Traditional
- For numplayer enter either 0, 1 or 2, 0 means that it will have two AI's play each other. 1 means that there is only one player so you will play a computer and 2 means that there will be two players so you will take turns on the computer to play eachother
- For ai_skill_level whether you have one or two numbers depends on how many AI's you are using. If you chose to have one or no AI's then you only need to input one number (0 for random moves AI and 1 for the better AI) but if you choose two AI's to play against each other then you you will need to choose the skill level of the black and white pieces. The first number is the AI skill level for the black pieces and the second number is the AI skill level for the white pieces. 
- Use the arrow keys to move the cursor on the chess board
- To select a piece move your cursor over the preferred piece and then press the spacebar to show all possible moves
- To move the selected piece to one of the possible moves, move your cursor to the preferred move and press the spacebar

*NOTE: The boards look best in dark mode, they work in light mode however, it may be harder to tell the pieces apart



Tips:
- If the arrow keys are not working, try clicking on the chessboard and then try the arrow keys again
- If you are not able to move a piece, it may be because you are in check or there are no open spots for the piece to move to
- The difference between the pieces are that one side is filled in and the other side is hollowed out, it may be easier to see the board if you zoom in the page

Important Parts of the Code:

=====Game Logic======
The board is stored as a 2D array of integers. Each piece is identified by a unique integer. The main gameplay loop consists of getting a list of all legal moves, then choosing one of the moves to play on the board. Both players go back and forth getting legal moves and picking one to play until a player is checkmated or stalemate occurs.

Major Game Logic Functions:
  
- getLegalMoves() -
Takes as input a board state (2D array of integers with dimesions [8][8]) and an integer to represent which color to get legal moves for.

- sweep() -
Takes as input a board state, an x and y coordinate for a position on the board, and two integers to represent change in the x and y directions. Will output a sweep_struct which contains how many empty squares are in the given direction from the coordinate given and the piece that blocks the sweep from moving forward. This is used when gathering legal moves from pieces that go straight in one direction until it hits a piece or a wall such as the rook, bishop, and queen.

- knight() -
Takes as input a board state, y and x coordinates, and two inputs corresponding to a direction a knight could hop. This function outputs whatever piece the knight would land on if it went in that direction.
    
- check() -
Takes as input a board state and a color and outputs whether the king of that color is in check in the given board state.

- makeMove() -
Takes as input a board state, initial coordinates, and new coordinates. Will create a struct called "amove" which keeps track of attributes a move could have such as if a piece is captured from it or a king is put in check.

- selfcheck() -
Takes as input a board state, a move struct, it then outputs whether the given move puts the player who made the move in check. This is needed because these moves are illegal and we must prevent them from being added to the legal moves list

- updateBoard() -
Takes as input a board state and a move and applies the given move to the board array.

- checkmate() -
Takes as input a board state and a color. This function outputs whether that color is in checkmate in the given board state.



=====Printing the Board=====

   - We used ncurses to print out our board and unicode for the peices, the function to print the board is called printBoard and the function that is called in printBoard to print the pieces is called printPieces. In printboard we used color pairs to define the different themes along with for loops and if statements to create the usual checkered pattern. For the printPieces we had to define each unicode peice individually in order to print it on the ncurses board. 


===== AI =====
In a seperate c file called "basic_ai" we include within the header of the main.c file is a function called myAi(). This function takes as input a list of moves and then outputs a single move. The way our AI works is it has 3 priorities. If it cannot satisfy the first priority it will go on to the next one and so on.

  Priority 1: Capture an enemy piece
  Priority 2: Put the enemy king in check
  Priority 3: Choose whatever moves pushes a piece furthest into enemy territory

