#ifndef LOGIC_H
#define LOGIC_H

#include <vector>

int GetCellValue(const std::vector< std::vector<int> >& board, int i, int j);
int GetNeighbours(const std::vector< std::vector<int> >& board, int i, int j);
int EvalCell(const std::vector< std::vector<int> >& board, int i, int j);
void NextGeneration(std::vector< std::vector<int> >& board);

#endif
