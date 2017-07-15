#include "data.h"

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


