#include <string>
#include "data.h"
#include "gui.h"

int main(int argc, char* args[]){
	int interval = 500;
	int gui = 0;
	int windowWidth = 640;
	int windowHeight = 480;
	if(argc > 1){
		interval = std::stoi(args[1]);
	}
	if(argc > 4){
		gui = std::stoi(args[2]);
		windowWidth = std::stoi(args[3]);
		windowHeight = std::stoi(args[4]);
	}


	auto board = LoadBoard("board.txt");
	if(gui)
		return InitWindow(interval, windowWidth, windowHeight, board);
	else
		return InitConsole(interval, board);
}


