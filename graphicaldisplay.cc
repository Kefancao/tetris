#include "graphicaldisplay.h"
#include "board.h"
#include "cell.h"
#include <string>
#include <iostream> 

const int BOARD_WIDTH = 110; 
const int GRID_SPACE = 20; 
const int IND_GRID_WIDTH = GRID_SPACE / 10; 
const int IND_GRID_HEIGHT = 10 * 18; // where 10 is the boardLength; 
const int FREE_WIDTH = BOARD_WIDTH - GRID_SPACE; 

using std::to_string;

GraphicalDisplay::GraphicalDisplay(int width, int height) :
    Xwindow{width, height} {
        reset(0); 
    }

void GraphicalDisplay::reset(int _highScore) {
    fillRectangle(0, 0, 400, 400, Xwindow::White);

    // Top Horizontal, -2 is to draw from above so as to not violate blocks
    fillRectangle(
        topLeftBoard1.x, topLeftBoard1.y + 50 + 3 * blockLength - 2,
        blockLength * 11, 2, 1); 
    // Left
    fillRectangle(
        topLeftBoard1.x - 2, topLeftBoard1.y + 50 + 3 * blockLength - 2,
        2, IND_GRID_HEIGHT + 2, 1); 
    // Bottom Horizontal
    fillRectangle(
        topLeftBoard1.x, topLeftBoard1.y + 50 + 21 * blockLength - 2,
        blockLength * 11, 2, 1);  
    // Right
    fillRectangle(
        topLeftBoard1.x + blockLength * 11 - 2, topLeftBoard1.y + 50 + 3 * blockLength - 2,
        2, IND_GRID_HEIGHT + 2, 1); 
        
    fillRectangle(
        topLeftBoard2.x, topLeftBoard2.y + 50 + 3 * blockLength - 2,
        blockLength * 11, 2, 1); 
    // Left
    fillRectangle(
        topLeftBoard2.x - 2, topLeftBoard2.y + 50 + 3 * blockLength - 2,
        2, IND_GRID_HEIGHT + 2, 1); 
    // Bottom Horizontal
    fillRectangle(
        topLeftBoard2.x, topLeftBoard2.y + 50 + 21 * blockLength - 2,
        blockLength * 11, 2, 1);  
    // Right
    fillRectangle(
        topLeftBoard2.x + blockLength * 11 - 2, topLeftBoard2.y + 50 + 3 * blockLength - 2,
        2, IND_GRID_HEIGHT + 2, 1); 

    for (int i = 0; i < 10; ++i){
        fillRectangle(topLeftBoard1.x + 8 * (i + 1) + 2 * i, topLeftBoard1.y + 50 + 3 * blockLength, 2, IND_GRID_HEIGHT, 1); 
        fillRectangle(topLeftBoard2.x + 8 * (i + 1) + 2 * i, topLeftBoard2.y + 50 + 3 * blockLength, 2, IND_GRID_HEIGHT, 1); 
    }

    for (int i = 0; i < 17; ++i){
        int color = i == 2 ? 6 : 1; 
        fillRectangle( topLeftBoard1.x, topLeftBoard1.y + 50 + 3 * blockLength + 8 * (i + 1) + 2 * i, blockLength * 11, 2, color); 
        fillRectangle( topLeftBoard2.x, topLeftBoard2.y + 50 + 3 * blockLength + 8 * (i + 1) + 2 * i, blockLength * 11, 2, color); 
    }

    int xCoord = topLeftBoard1.x;
    int yCoord = 250;
    drawString(xCoord, yCoord + 40, "Next: ");
    xCoord = topLeftBoard2.x;
    drawString(xCoord, yCoord + 40, "Next: ");
    setHighScore(_highScore); 
}

void GraphicalDisplay::notify(Cell &s) {
    Coordinates topLeft = s.getBoardNum() == 1 ? topLeftBoard1 : topLeftBoard2;
    int xCoord, yCoord;
    if (s.isNext()) {
        xCoord = topLeft.x + s.getX() * blockLength + 4 * blockLength;
        yCoord = topLeft.y + 250 + 40 + s.getY() * blockLength;
    } else {
        xCoord = topLeft.x + s.getX() * blockLength;
        yCoord = topLeft.y + 50 + ( 3+ s.getY()) * blockLength; // +50 to leave space for score/level
    }
    char blockType = s.getBlockType(); 
    int col; 
    switch(blockType){
        case 'L':
            col = Xwindow::TetOrange; 
            break; 
        case 'O': 
            col = Xwindow::TetYellow; 
            break; 
        case 'S': 
            col = Xwindow::TetGreen; 
            break; 
        case 'Z': 
            col = Xwindow::TetRed; 
            break; 
        case 'J': 
            col = Xwindow::TetBlue; 
            break; 
        case 'I': 
            col = Xwindow::TetSky; 
            break; 
        case 'T': 
            col = Xwindow::TetPurple; 
            break; 
        case ' ':   // empty
            col = Xwindow::White;
            break;
        case '?':   // blind
            col = Xwindow::Black;
            break;
        case '*': 
            col = Xwindow::TetBrown; 
            break;
        default: 
            col = Xwindow::Black; 
            break; 
    }
    fillRectangle(xCoord, yCoord, blockLength -2, blockLength - 2, col); // -2 to save space for border. 
}

void GraphicalDisplay::updateScore(int score, int boardNum) {
    Coordinates topLeft = boardNum == 1 ? topLeftBoard1 : topLeftBoard2;
    int xCoord = topLeft.x;
    int yCoord = 50;
    fillRectangle(xCoord - 5, yCoord - 15, 70, 20, Xwindow::White);
    drawString(xCoord, yCoord, "Score: " + to_string(score));
}

void GraphicalDisplay::updateLevel(int level, int boardNum) {
    Coordinates topLeft = boardNum == 1 ? topLeftBoard1 : topLeftBoard2;
    int xCoord = topLeft.x;
    int yCoord = 70;
    fillRectangle(xCoord - 5, yCoord - 15, 70, 20, Xwindow::White);
    drawString(xCoord, yCoord, "Level: " + to_string(level));
}

void GraphicalDisplay::setHighScore(int _highScore){
    highScore = _highScore;
    int xCoord = 140; 
    int yCoord = 30;
    fillRectangle(xCoord - 5, yCoord - 15, 70, 20, Xwindow::White);
    drawString(xCoord, yCoord, "High Score: " + to_string(highScore));
}

