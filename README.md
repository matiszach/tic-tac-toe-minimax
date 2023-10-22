# tic-tac-toe-minimax-
My Tic-tac-toe implementation, which always plays optimal moves based on the Minimax algorithm

# Description

Tic-tac-toe is a simple game played on a 3x3 grid, where two players make alternating moves by choosing an empty tile and putting their symbol there ('O' and 'X'). A player who is the first to fill an entire row, column, or diagonal with his symbols is considered a winner. If there are no empty tiles left and no one has won, the game is considered a tie.

# Algorithm

Every position will be marked as one of the three possible states assuming both players play optimally
1. O wins
2. X wins
3. Tie

For positions where the game has ended, it is known what the state is. Therefore, the algorithm will assign states to the positions in the reverse order starting from the already ended positions and going back to the initial game position.

Now, knowing what are the outcomes of all the positions achievable from the current position, it is easy to determine what is the state of the current position and what is the best move to make.

The technique used here is called [Minimax algorithm](https://en.wikipedia.org/wiki/Minimax).

## Analysis

The program has to search through all the game positions to calculate the best possible move. But there are only 765 possible game positions, so the algorithm runs fast.

# Usage

To use the program you need to compile it first using C++ 17 or higher.
```
g++ -std=c++17 -o tictactoe tictactoe.cpp
```
Then run it

```
./tictactoe
```

You are the player with the symbol 'X', program takes as input coordinates of the tile you want to place your symbol (coordinates are in the format (row, column) for instance 2 3 means a tile in the second row and third column)

## Example

```
+---+---+---+
|   |   |   |
+---+---+---+
|   |   |   |
+---+---+---+
|   |   |   |
+---+---+---+
Your move X: 2 2

+---+---+---+
| O |   |   |
+---+---+---+
|   | X |   |
+---+---+---+
|   |   |   |
+---+---+---+
Your move X: 1 3

+---+---+---+
| O |   | X |
+---+---+---+
|   | X |   |
+---+---+---+
| O |   |   |
+---+---+---+
Your move X: 2 1

+---+---+---+
| O |   | X |
+---+---+---+
| X | X | O |
+---+---+---+
| O |   |   |
+---+---+---+
Your move X: 1 2

+---+---+---+
| O | X | X |
+---+---+---+
| X | X | O |
+---+---+---+
| O | O |   |
+---+---+---+
Your move X: 3 3

+---+---+---+
| O | X | X |
+---+---+---+
| X | X | O |
+---+---+---+
| O | O | X |
+---+---+---+
TIE!
```
