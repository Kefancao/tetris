# Tetris-2p
This game is an alternate version of traditional tetris. The main difference being that players enable a special action to be enacted on the other player 
if the current player clears two rows, because of this and the higher levels in this game, in this version of tetris, the blocks do not move down, but 
instead requires the player to move the blocks down and drop them. 
The game has a text mode playable on your command-line, a textGUI mode made with ncurses, as well as a GUI mode
which requires the X11 library to compile.

## Compilation 
To compile the game, use the Makefile provided

## Flags/Command line arguments 
The game has several command line arguments available. Below are what's supported. 
* `-textGUI` -> Runs the game in the textGUI mode, highly recommended for game play. 
* `-text` -> Runs the game in text only mode. 
* `-startlevel n` -> Runs the game in the respective level. 
If no flags are passed in, then the game starts in level 0 and is played in text mode with a GUI enabled. 

## Game Play 
### Levels 
Each of the levels in this game has a different probability of how blocks occur. Of course, the higher the level, the less 'easy' blocks will occur. Additionally, 
levels 3 and 4 have a special property applied to the blocks, blocks in levels 3 and 4 are considered 'weighted', meaning for every move to the left, right, clockwise 
or counterclockwise rotation, the blocks drop down by one row, making it harder to place a block in the desired position. 

There is one major difference between level 3 and 4. In level 4, if the player has not cleared a row after 5 moves, then a brown block will be dropped in the center
column of the game board. This brown block will behave like any other block and can be cleared. 

### General Rules/ Special Actions 
In this game. If a player successfully clears 2 rows in one drop, he/she triggers a special action which is applied to the opponent's board. There are three special actions 
that can be activated. 
* **blind** - This will blind a section of the opponent's board, making it difficult for them to drop their block. 
* **heavy** - This will make the opponent's block weighted, meaning it will be substantially harder for them to drop a block. 
* **force** - This will force the opponent's block of the block of your choice. 

### Controls 
* `Left arrow key` Moves the current block to the left by one.
* `Right arrow key` Moves the current block to the right by one.
* `Up arrow key` Rotates the current block clockwise. 
* `Down arrow key` Moves the current block down by one row. 
* `z` Rotates the current block counterclockwise. 
* `Space` Drops the current block. 
