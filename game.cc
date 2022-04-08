#include "game.h" 
#include "board.h"
#include "graphicaldisplay.h"
#include "breakException.h"
#include "textdisplay.h"
#include "ncurses.h"
#include <sstream>
#include <iomanip>

using std::string; 
using std::make_shared;
using std::pair;
using std::cin; 
using std::cout;
using std::endl;
using std::istringstream;
using std::make_pair;
using std::to_string;
using std::ios_base;

const int BACKGROUND = 1; 
const int O_BLOCK = 2;
const int I_BLOCK = 3; 
const int J_BLOCK = 4; 
const int L_BLOCK = 5; 
const int S_BLOCK = 6; 
const int Z_BLOCK = 7; 
const int T_BLOCK = 8; 
const int TEXT = 9; 
const int BLIND = 10; 
const int B_BLOCK = 11; 

Game::Game(string inFile1, string inFile2, bool textOnly, bool textGUI, int initLvl, int seed) : 
	inFile1{inFile1}, inFile2{inFile2}, singlePlayer{false}, highScore{0}, 
	textGUI{textGUI}, initLvl{initLvl}, sequenceCount{0}, seed{seed}
{
	if (textOnly) gui = nullptr;
	else gui = make_shared<GraphicalDisplay>();
	player1 = make_shared<Board>(Coordinates{0, 0}, textGUI, inFile1, gui, 1, initLvl, seed); 	
	player2 = make_shared<Board>(Coordinates{15, 0}, textGUI, inFile2, gui, 2, initLvl, seed); 
	if (!textGUI) {
		cout << "\nWelcome to biquadris." << endl;
		cout << "Enter \"hint\" if you want to see a list of the commands." << endl;
	}
	cur = player1;
	updateHighScore(); 
	player1->getTD()->setScore(0, highScore);
}

void Game::playGame() { 
	if (!textGUI) print();
	else {
		// For the textGUI ncurses; 
		initscr();
		clear();
		noecho();
		cbreak();
		start_color(); 
		init_pair(BACKGROUND, COLOR_BLACK, COLOR_BLACK); 
		init_pair(BLIND, COLOR_WHITE, COLOR_WHITE); 
		init_pair(TEXT, COLOR_WHITE, COLOR_BLACK); 
		init_pair(O_BLOCK, COLOR_YELLOW, COLOR_YELLOW); 
		init_pair(J_BLOCK, COLOR_BLUE, COLOR_BLUE); 
		init_pair(L_BLOCK, COLOR_MAGENTA, COLOR_MAGENTA); 
		init_pair(I_BLOCK, COLOR_CYAN, COLOR_CYAN); 
		init_pair(S_BLOCK, COLOR_GREEN, COLOR_GREEN); 
		init_pair(T_BLOCK, COLOR_MAGENTA, COLOR_MAGENTA); 
		init_pair(Z_BLOCK, COLOR_RED, COLOR_RED);
		init_color(100, 163, 100, 28); 
		init_pair(B_BLOCK, 100, 100); 
		keypad(stdscr, true);
		player1->getTD()->display(); 
		player2->getTD()->display(); 
	}
	while (true) {
		
		try { doCmd(determineCmd()); }
		catch (BreakException&) {
			if (textGUI){
				endwin(); 
			} 

			return; 
		}
	}
}

void Game::newGame() {
	updateHighScore();
	if (gui) gui->reset(highScore);
	player1 = make_shared<Board>(Coordinates{0, 0}, textGUI, inFile1, gui, 1, initLvl); 
	player2 = make_shared<Board>(Coordinates{15, 0}, textGUI, inFile2, gui, 2, initLvl); 
	player1->getTD()->setScore(0, highScore);
	if (textGUI){
		player1->getTD()->display(); 
		player2->getTD()->display(); 
	}
	cur = player1; 
	singlePlayer = false;
}

void Game::switchBoard() {
	cur = cur.get() == player1.get() ? player2 : player1;
}

void Game::updateHighScore() {
	highScore = highScore > player1->getScore() ? highScore : player1->getScore(); 
	highScore = highScore > player2->getScore() ? highScore : player2->getScore();
}

void Game::print() {
	cout << endl << "        Highscore: " << highScore << endl;
	cout << "Level:" << std::setw(7) << player1->getLevel() << "\tLevel:" << std::setw(7) << player2->getLevel() << endl; 
	cout << "Score:" << std::setw(7) << player1->getScore() << "\tScore:" << std::setw(7) << player2->getScore() << endl; 
	string borderLine(11, '-'); 
	borderLine = 'x' + borderLine + 'x'; 
	borderLine = borderLine + '\t' + borderLine; 
	cout << borderLine << endl; 
	for (size_t i = 0; i < 18; ++i){
		player1->printLine(i); 
		cout << "\t"; 
		player2->printLine(i); 
		cout << endl; 
	}
	cout << borderLine << endl; 
	for (size_t i = 0; i < 2; ++i) {
		if (i == 0) cout << "Next: ";
		else cout << "      ";
		player1->printLineNext(i);
		if (i == 0) cout << "\tNext: ";
		else cout << "\t      ";
		player2->printLineNext(i);
		cout << endl; 
	}
}

static string levelParse(int desiredLvl, int currentLvl){
	int diff = desiredLvl - currentLvl; 
	if (diff > 0) return std::to_string(diff) + "levelup"; 
	if (diff < 0) return std::to_string(-diff) + "leveldown"; 
	return "ignore"; 
}

pair<Command, int> Game::determineCmd() {
	string input; 
	bool isZero = false;
	if (!textGUI) {
		readString(input);
		isZero = input[0] == '0';
	}
	else {
		// For textGUI ncurses; 
		Start: 
		int comm = getch(); 
		switch (comm){
			case KEY_LEFT: 
				input = "left"; 
				break; 
			case KEY_RIGHT: 
				input = "right"; 
				break; 
			case KEY_DOWN: 
				input = "down"; 
				break; 
			case KEY_UP: 
				input = "clockwise"; 
				break;  
			case ' ': 
				input = "drop"; 
				break; 
			case 'z': 
				input = "counterclockwise"; 
				break; 
			case 'q':
				throw BreakException{};
			case 'r':
				input = "restart";
				break; 
			case '0':
				input = levelParse(0, cur->getLevel()); 
				break; 
			case '1':
				input = levelParse(1, cur->getLevel()); 
				break; 
			case '2':
				input = levelParse(2, cur->getLevel()); 
				break; 
			case '3':
				input = levelParse(3, cur->getLevel()); 
				break; 
			case '4':
				input = levelParse(4, cur->getLevel()); 
				break; 
			case 's': 
				goto Start; 
			default: 
				input = string(1, comm); 
				break; 
		}
	}
	istringstream iss(input); 
	int mult = 1; 
	iss >> mult >> input;
	vector<string> commands, toPush; 
	for (auto& n : commandPairs) commands.push_back(n.first); 
	pair<Command, int> retval; 
	retval.second = mult ? mult : 1;
	retval.second = isZero ? 0 : retval.second;
	// Add 1 to input.size() as a cushion for checking if the word is a perfect match. 
	// invariant : The user input may not be identical to two commands simultaenous for the 
	//                first x chars and for the x+1 char does not match either of them. 
	for (size_t i = 0; i < input.size() + 1; ++i){
		for (size_t j = 0; j < commands.size(); ++j){
			if (commands.size() == 1){
				retval.first = commandPairs[commands[0]]; 
				return retval; 
			}  
			if (commands[j][i] == input[i]){
				toPush.push_back(commands[j]); 
			}
		}
		commands.clear(); 
		for (auto n : toPush) commands.push_back(n); 
		toPush.clear(); 
	}
	return retval; 
}

static bool isMoveCmd(Command cmd) {
	return cmd == Left || cmd == Right || 
		   cmd == Clockwise || cmd == Counterclockwise || 
		   cmd == Down;
}

static bool isForceCmd(Command cmd) {
	return cmd == I || cmd == J || cmd == L || cmd == O || 
		   cmd == S || cmd == T || cmd == Z;
}

void Game::showHint() {
	if (textGUI) return;
	cout << "\nAvailable commands:" << endl;
	cout << "\"left\", \"right\", \"clockwise\", \"counterclockwise\", \"down\"," << endl;
	cout << "\"drop\", \"levelup\", \"leveldown\", \"restart\"" << endl;
}


void Game::doCmd(pair<Command, int> cmd) {
	Command action = cmd.first;
	int mult = cmd.second;

	if (mult == 0) goto End;

	if (action == Restart) {
		newGame();
		if (!textGUI) print();
		else cur->getTD()->display(); 
		return;
	}

	if (action == Drop) {
		int rowsCleared = cur->dropBlock();
		cur->setBlind(false); // unblind the board after each drop
		if (!textGUI) print();
		else cur->getTD()->display(); 
		if (!singlePlayer) {
			switchBoard();
			if (rowsCleared >= 2) specialAction();
		}
		if (rowsCleared == -1) gameOver();
		if (mult == 1) return; 
		else doCmd(make_pair(Drop, mult-1));
		return;
	}

	if (action == Sequence) {
		string file;
		readString(file);
		try {
			in = make_shared<std::ifstream>(file);
			in->exceptions(ios_base::failbit); 
			sequenceCount = mult;
	    } catch (ios_base::failure&) {
			sequenceCount = 0;
			cout << "Could not open input file." << endl;
	    }
	}  

	if (action == Hint) showHint();

	if (action == LevelUp) cur->increaseLevel(mult);
	if (action == LevelDown) cur->decreaseLevel(mult);

	if (action == Random) cur->setRandom(true); 
	if (action == NoRandom) cur->setRandom(false); 

	if (isMoveCmd(action)) {
		cur->moveBlock(cmd);
		if (cur->isCurrentHeavy() && action != Down && !cur->moveBlock(make_pair(Down, 1))) {
			doCmd(make_pair(Drop, 1));
		}
	}

	if (isForceCmd(action) && !cur->force(action)) gameOver();

	End:
	if (!textGUI) print(); 
	else cur->getTD()->display(); 
}

void Game::specialAction() {
	string action;
	if (!textGUI) cout << "Enter a special action" << endl << " - blind" << endl << " - force <block>" << endl << " - heavy" << endl;
	else action = player1->getTD()->specialAction(); 
	while (true) {
		if (!textGUI){
			readString(action);
		}
		if (action == "blind") {
			cur->setBlind(true);
			break;
		} else if (action == "heavy") {
			cur->makeCurrentHeavy();
			break;
		} else if (action == "force") {
			string b;
			if (!textGUI) readString(b);
			else{
				int i = getch(); 
				b = string(1, i); 
			}
			while (b != "I" && b != "J" && b != "L" && b != "O" && 
					b != "S" && b != "T" && b != "Z") {
						if (!textGUI) readString(b);
						else{
							int i = getch(); 
							b = string(1, i); 
						}
					}
			if (!cur->force(commandPairs[b])) gameOver();
			break;
		}
	}
	if (!textGUI) print();
	else cur->getTD()->display(); 
}

void Game::gameOver() {
	string winner = cur.get() == player1.get() ? "Player 2" : "Player 1";
	auto loser = (winner == "Player 1" ? player1 : player2); 
	string choice;
	if (!textGUI) {
		if (!singlePlayer) {
			cout << winner << " finished with " << loser->getScore() << endl;
			cout << "Enter C to continue playing." << endl;
		} else {
			string higher = player1->getScore() > player2->getScore() ? "Player 1" : "Player 2"; 
			if (player1->getScore() != player2->getScore())
				cout << "Game over. " << higher << " won. Enter G for a new game." << endl;
			else cout << "Tie game. Enter G for a new game." << endl; 
		}
		readString(choice);
	} else {
		string message = winner + " finished with " + std::to_string(loser->getScore()) + ". Enter C to continue playing."; 
		if (singlePlayer){
			string higher = player1->getScore() > player2->getScore() ? "Player 1" : "Player 2"; 
			message = "Game over. " + higher + " won. Enter G for a new game.";
			if (player1->getScore() == player2->getScore()){
				message = "Tie game. Enter G for a new game."; 
			}
		}
		choice = string(1, player1->getTD()->playAgain(message)); 
	}
	if (choice == "G" || choice == "g") {
		newGame();
		if (!textGUI) print();
		else cur->getTD()->display(); 
	} else if ((choice == "C" || choice == "c") && !singlePlayer) {
		singlePlayer = true;
		if (!textGUI) print();
		else cur->getTD()->display(); 
	} else throw BreakException{};
}

void Game::readString(string& s) {
	if (sequenceCount) {
		try{
			*in >> s;
		}
		catch (std::ios::failure&){
			--sequenceCount;
			in->clear(); 
			in->seekg(0, in->beg);
			readString(s); 
		}
	} else {
		cin >> s;
		if (cin.eof()) throw BreakException{}; 
	}
}
