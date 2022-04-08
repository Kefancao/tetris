#include "board.h"
#include "blocksList.h"
#include "cell.h"
#include "subject.h"
#include "level.h"
#include "level3.h"
#include "level0.h"
#include "level4.h"
#include "textdisplay.h"
#include "graphicaldisplay.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using std::vector; 
using std::string; 
using std::shared_ptr; 
using std::make_shared; 
using std::make_pair;

Board::Board(Coordinates textCoord, bool textGUI, string inFile, 
			shared_ptr<GraphicalDisplay> gui, int myNum, int initLvl, int seed) : 
	score{0}, cur{nullptr}, next{nullptr}, gui{gui}, myNum{myNum}, blind{false}, fileName{inFile}
{
	td = make_shared<TextDisplay>(textCoord, textGUI); 
	factory = make_shared<Level0>(seed); 
	dynamic_cast<Level0&>(*factory).setFileName(inFile); 
	while (factory->getLevel() != initLvl) factory = factory->increase(); 
	for (int i = 0; i < 18; ++i){
		vector<shared_ptr<Cell>> row; 
		for (int j = 0; j < 11; ++j){
			auto cell = make_shared<Cell>(j, i); 
			cell->setBoardNum(myNum);
			cell->setNext(false);
			cell->attach(td);
			if (gui) cell->attach(gui); // for text only mode
			row.push_back(cell); 
		}
		grid.push_back(row); 
	}
	for (int i = 0; i < 2; ++i){
		vector<shared_ptr<Cell>> row; 
		for (int j = 0; j < 4; ++j){
			auto cell = make_shared<Cell>(j, i);
			cell->setBoardNum(myNum);
			cell->setNext(true);
			cell->attach(td);
			if (gui) cell->attach(gui); // for text only mode
			row.push_back(cell); 
		}
		nextGrid.push_back(row); 
	}
	blockCreate(); 
	if (gui) {
		gui->updateLevel(getLevel(), myNum);
		gui->updateScore(getScore(), myNum);
	}

	td->setScore(getScore()); 
	td->setLevel(getLevel()); 
}


static BlockTypes cmdToBT(Command c) {
	switch (c) {
		case I: return BlockTypes::I; 
		case J: return BlockTypes::J;
		case L: return BlockTypes::L;
		case O: return BlockTypes::O;
		case S: return BlockTypes::S;
		case T: return BlockTypes::T;
		case Z: return BlockTypes::Z;
		default: return BlockTypes::Nothing; 
	}
}
 
bool Board::force(Command cmd) {
	for (auto p : cur->getPositions()){
		setCell(p, nullptr, true); 
	}
	for (size_t i = 0; i < blocks.size(); ++i) {
		if (blocks[i] == cur) {
			blocks.erase(blocks.begin() + i);
			break;
		}
	}
	cur = factory->make(cmdToBT(cmd));
	cur->setLevel(factory->getLevel());
	for (auto p : cur->getPositions()){
		if (grid[p.y][p.x]->isOccupied()) return false; 
	}
	for (auto p : cur->getPositions()){
		setCell(p, cur, true); 
	}
	
	blocks.emplace_back(cur);
	return true;
}

bool Board::blockCreate() {
	if (next) cur = next;	// no next at the beginning
	else {
		cur = factory->make(); 
		cur->setLevel(factory->getLevel());
	}
	next = factory->make();
	next->setLevel(factory->getLevel());
	for (auto p : cur->getPositions()){
		if (grid[p.y][p.x]->isOccupied()) return false; 
	}
	for (auto p : cur->getPositions()){
		setCell(p, cur, true); 
	}
	clearNext();
	for (auto p : next->getPositions()){
		p.y -= 2;
		setCellNext(p, next); 
	}
	blocks.emplace_back(cur);
	return true;
}

bool Board::brownBlockCreate() {
	bool make = (factory->getLevel() == 4 && dynamic_cast<Level4&>(*factory).isMakeBrown()) ? true : false; 
	if (!make) return blockCreate();
	cur = dynamic_cast<Level4&>(*factory).makeBrown(); 
	cur->setLevel(factory->getLevel());
	for (auto p : cur->getPositions()){
		if (grid[p.y][p.x]->isOccupied()) return false; 
	}
	for (auto p : cur->getPositions()){
		setCell(p, cur, true); 
	}
	blocks.emplace_back(cur);
	dropBlock();
	return true;
}

int Board::dropBlock() {
	// Be careful with the order of this function. 
	moveBlock(make_pair(Down, 100)); // any number larger than the board's height 
	int count = clearRows();
	if (count && factory->getLevel() == 4) dynamic_cast<Level4&>(*factory).setCleared(true);
	bool success = brownBlockCreate();
	if (count) {
		score += pow(count + getLevel(), 2);
		for (size_t i = 0; i < blocks.size();) {
			if (blocks[i].use_count() == 1) {
				score += pow(blocks[i]->getLevel() + 1, 2);
				blocks.erase(blocks.begin() + i);
			} else ++i;
		}
		if (gui) gui->updateScore(getScore(), myNum);
		td->setScore(getScore()); 
	}

	if (!success) return -1;
	return count; 
}

void Board::increaseLevel(int mult){
	bool updated = false;
	while (mult && getLevel() != 4) {
		factory = factory->increase();
		updated = true; 
		--mult;
	}
	if (updated && gui) gui->updateLevel(getLevel(), myNum);
	td->setLevel(getLevel()); 
}

void Board::decreaseLevel(int mult){
	bool updated = false;
	while (mult && getLevel() != 0) {
		factory = factory->decrease(); 
		if (factory->getLevel() == 0){
			dynamic_cast<Level0&>(*factory).setFileName(fileName); 
		}
		updated = true; 
		--mult;
	}
	if (updated && gui) gui->updateLevel(getLevel(), myNum);
	td->setLevel(getLevel()); 
}

void Board::setBlind(bool _blind){
	// fix the row and column numbers 
	if (blind == _blind) return;
	else blind = _blind;
	for (auto& row : grid) {
		for (auto cell : row) {
			if (cell->getY() >= 3 && cell->getY() <= 12 
				&& cell->getX() >= 2 && cell->getX() <= 8) {
				cell->setBlind(blind);
			}
		}
	}
}


void Board::setRandom(bool random){
	if (factory->getLevel() < 3) return;
	string s;  
	if (factory->getLevel() == 4){
		if (dynamic_cast<Level4&>(*factory).getRandom() == random) return; 
		if (random) dynamic_cast<Level4&>(*factory).setRandomOn();
		else{
			std::cin >> s; 
			dynamic_cast<Level4&>(*factory).setRandomOff(s); 	
		}
	}
	else{
		if (dynamic_cast<Level3&>(*factory).getRandom() == random) return; 
		if (random) dynamic_cast<Level3&>(*factory).setRandomOn();
		else{
			std::cin >> s; 
			dynamic_cast<Level3&>(*factory).setRandomOff(s); 	
		}
	}
	return; 
}

bool Board::isCurrentHeavy(){
	return cur->isHeavy();
}

void Board::makeCurrentHeavy(){
	cur->makeHeavy(); 
}

int Board::getScore(){
	return score; 
}

int Board::getLevel(){
	return factory->getLevel(); 
}

void Board::setCell(Coordinates c, shared_ptr<Block> block, bool notify){
	grid[c.y][c.x]->setBlock(block); 
	if (notify) grid[c.y][c.x]->notifyObservers();
}

void Board::setCellNext(Coordinates c, shared_ptr<Block> block){
	nextGrid[c.y][c.x]->setBlock(block); 
	nextGrid[c.y][c.x]->notifyObservers();
}

void Board::clearNext() {
	for (auto& row : nextGrid) {
		for (auto cell : row) {
			cell->setBlock(nullptr);
			cell->notifyObservers();
		}
	}
}

bool Board::moveBlock(pair<Command, int> cmd) {
	vector<Coordinates> oldPositions = cur->getPositions();
	Command action = cmd.first;
	int mult = cmd.second;
	// rotations are mod 4. But what if it can't rotate all around? Therefore mod 8
	if (action == Clockwise || action == Counterclockwise) mult %= 8;
	int moved = false;
	for (; mult; --mult) {
		if (!moveBlockOnce(action)) break;
		moved = true;
	}
	if (!moved) return false;
	for (auto p : oldPositions) setCell(p, nullptr, true);
	for (auto p : cur->getPositions()) setCell(p, cur, true);
	return true;
}

bool Board::moveBlockOnce(Command cmd) {
	bool success = true;
	vector<Coordinates> oldPositions = cur->getPositions();
	for (auto p : oldPositions) setCell(p, nullptr, false);

	switch (cmd) {
		case Right:
			cur->right();
			if (!successfulMove()) {
				cur->left();
				success = false;
			}
			break;
		case Left:
			cur->left();
			if (!successfulMove()) {
				cur->right();
				success = false;
			}
			break;
		case Clockwise:
			cur->clockwise();
			if (!successfulMove()) {
				cur->counterclockwise();
				success = false;
			}
			break;
		case Counterclockwise:
			cur->counterclockwise();
			if (!successfulMove()) {
				cur->clockwise();
				success = false;
			}
			break;
		case Down:
			cur->down();
			if (!successfulMove()) {
				cur->up();
				success = false;
			}
			break;
		default: 
			break; 
	}

	for (auto p : cur->getPositions()) setCell(p, cur, false);
	return success;
}

bool Board::successfulMove() {
	for (auto p : cur->getPositions()) {
		if (p.x < 0 || p.x > 10 || p.y < 0 || p.y > 17 || 
			grid[p.y][p.x]->isOccupied()) return false;
	}
	return true;
}

int Board::clearRows() {
	vector<int> rowsCleared; 
	// Determine which rows needs to be cleared
	for (size_t i = grid.size() - 1; i > 2; --i){
		for (size_t j = 0; j < grid[i].size(); ++j){
			if (!grid[i][j]->getBlock()) goto loopEnd; 
		}
		rowsCleared.push_back(i); 
		loopEnd: 
			continue; 
	}

	// Increments the rows need to be cleared as their relative position 
	//   once the preceding rows have been cleared. 
	for (size_t i = 1; i < rowsCleared.size(); ++i){
		for (size_t j = i; j < rowsCleared.size(); ++j){
			rowsCleared[j]++; 
		}
	}

	// Clear the rows. 
	for (auto n : rowsCleared){
		for (size_t i = n; i > 1; --i){
			for (size_t j = 0; j < grid[i].size(); ++j){
				setCell(Coordinates{int(j),int(i)}, grid[i-1][j]->getBlock(), true);
			}
		}
	}
	// Amount of rows cleared
	return rowsCleared.size(); 
}

void Board::printLine(int row) {
	td->printLine(row); 
}

void Board::printLineNext(int row) {
	td->printLineNext(row);
}

shared_ptr<TextDisplay> Board::getTD(){
	return td; 
}
