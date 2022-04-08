#include <iostream> 
#include <string>
#include <memory> 
#include <sstream>
#include "game.h"
#include "breakException.h"

using std::string; 
using std::stringstream; 

int main(int argc, char** argv){
	string inFile1 = "sequence1.txt"; 
	string inFile2 = "sequence2.txt";
	bool help = false, textOnly = false, textGUI = false; 
	int initLvl = 0, seed = 0; 
	for (int i = 1; i < argc; ++i){
		string command = string(argv[i]); 
		stringstream ss{command}; 
		ss >> command; 
		if (command == "-help") help = true;
		else if (command == "-scriptfile1" && !(ss >> inFile1)) inFile1 = argv[++i]; 
		else if (command == "-scriptfile2" && !(ss >> inFile2)) inFile2 = argv[++i]; 
		else if (command == "-seed" && !(ss >> seed)) seed = std::stoi(argv[++i]); 
		else if (command == "-textGUI") textGUI = true; 
		else if (command == "-text") textOnly = true; 
		else if (command == "-startlevel" &&  !(ss >> initLvl)) initLvl = std::stoi(argv[++i]); 
	}
	if (help) {
		std::cout << "Below are the options for running the program" << std::endl; 
		std::cout << " -scriptfile1 xxx    <-- Specifies the block intake file from level0" << std::endl; 
		std::cout << " -scriptfile1 xxx    <-- Specifies the block intake file from level0" << std::endl; 
		std::cout << " -seed xxx           <-- Specifies the seed to generate random blocks from" << std::endl; 
		std::cout << " -textGUI            <-- Plays the game in text GUI mode (ncurses)" << std::endl; 
		std::cout << " -startlevel n       <-- Plays the game for both players at level n" << std::endl; 
		std::cout << " -text               <-- Plays the game in text mode" << std::endl; 
		return 0;
	}
	if (textOnly) textGUI = false; 
	if (textGUI) textOnly = true; 
	std::shared_ptr<Game> game; 
	try{
		game = std::make_shared<Game>(inFile1, inFile2, textOnly, textGUI, initLvl, seed); 
	} catch (BreakException&){
		return 0; 
	}
	game->playGame(); 
}
