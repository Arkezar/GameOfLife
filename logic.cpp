#include "logic.h"

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
