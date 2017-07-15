#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <GLFW/glfw3.h>

void Print(const std::vector< std::vector<int> >& board){
	for(const auto& row : board){
		for(const auto& col : row){
			std::cout << (col == true ? "#" : " ");
		}
		std::cout << std::endl;
	}
}

void Draw(const std::vector< std::vector<int> >& board, int wWidth, int wHeight){
	int rows = board.size();
	int cols = board[0].size();

	int blockSize = wWidth / cols < wHeight / rows ? wHeight / rows : wWidth / cols;

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j]){
				int x = blockSize*j;
				int y = blockSize*i;
				glBegin(GL_QUADS);
				glVertex2i(x,y);
				glVertex2i(x+blockSize,y);
				glVertex2i(x+blockSize,y+blockSize);
				glVertex2i(x,y+blockSize);
				glEnd();
			}
		}
	}
}

int GetCellValue(const std::vector< std::vector<int> >& board, int i, int j){
	if(i < 0 || j < 0 || i == board.size() || j == board[0].size())
		return 0;
	else {
		return board[i][j];
	}
}

int GetNeighbours(const std::vector< std::vector<int> >& board, int i, int j){
	int result = 0;
	result += GetCellValue(board, i-1, j-1);
	result += GetCellValue(board, i-1, j);
	result += GetCellValue(board, i-1, j+1);
	result += GetCellValue(board, i, j+1);
	result += GetCellValue(board, i+1, j+1);
	result += GetCellValue(board, i+1, j);
	result += GetCellValue(board, i+1, j-1);
	result += GetCellValue(board, i, j-1);
	return result;
}

int EvalCell(const std::vector< std::vector<int> >& board, int i, int j){
	int aliveNg = GetNeighbours(board, i,j);	
	if(board[i][j] == 0){
		if(aliveNg == 3)
			return 1;
		else
			return 0;
	} else {
		if(aliveNg == 2 || aliveNg == 3)
			return 1;
		else
			return 0;
	}
}

void NextGeneration(std::vector< std::vector<int> >& board){
	auto newBoard = board;
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board[0].size(); j++){
			newBoard[i][j] = EvalCell(board, i,j);			
		}
	}
	board = newBoard;
}

std::vector< std::vector<int> > LoadBoard(std::string filepath){
	std::ifstream infile(filepath);
	std::vector< std::vector<int> > result;
	std::string line;
	while(std::getline(infile, line)){
		std::vector<int> row;
		for(const auto& c : line){
			row.push_back(c - '0');	
		}
		result.push_back(row);
	}
	return result;
}

int main(int argc, char* args[]){
	int interval = 500;
	int windowWidth = 640;
	int windowHeight = 480;
	if(argc > 1){
		interval = std::stoi(args[1]);
	}

	std::vector< std::vector<int> > board = LoadBoard("board.txt");
	
	GLFWwindow* window;
	if(!glfwInit())
		return -1;

	window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", NULL, NULL);
    	if (!window)
    	{
        	glfwTerminate();
        	return -1;
    	}

    	/* Make the window's context current */
	glfwMakeContextCurrent(window);

    	/* Loop until the user closes the window */
    	while (!glfwWindowShouldClose(window))
    	{
		glClearColor(0,0,0,0);

		/* Render here */
    	    	glClear(GL_COLOR_BUFFER_BIT);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, windowWidth, windowHeight, 0, 0, 1);
		Draw(board, windowWidth, windowHeight);
        	
		/* Swap front and back buffers */
        	glfwSwapBuffers(window);

        	/* Poll for and process events */
        	glfwPollEvents();

		NextGeneration(board);
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));	
    	}

    	glfwTerminate();
    	return 0;
}


