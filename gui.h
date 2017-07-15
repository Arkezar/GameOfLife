#ifndef GUI_H
#define GUI_H

#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <GLFW/glfw3.h>

void Print(const std::vector< std::vector<int> >& board);
void Draw(const std::vector< std::vector<int> >& board, int wWidth, int wHeight);
int InitConsole(int interval, std::vector< std::vector<int> > board);
int InitWindow(int interval, int width, int height, std::vector< std::vector<int> > board);
#endif
