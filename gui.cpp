#include "gui.h"
#include "logic.h"

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

int InitConsole(int interval, std::vector< std::vector<int> > board){
	while(1){
		Print(board);
		NextGeneration(board);
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));	

	}	
	return 0;
}


int InitWindow(int interval, int width, int height, std::vector< std::vector<int> > board){
	GLFWwindow* window;
	if(!glfwInit())
		return -1;

	window = glfwCreateWindow(width, height, "Game of Life", NULL, NULL);
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
		glOrtho(0, width, height, 0, 0, 1);
		Draw(board, width, height);
        	
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


