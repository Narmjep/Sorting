#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include "Block.h"

class Sorter
{
public:
	Sorter(int fps);
	~Sorter() = default;

	//general
	int fps = 0;
	bool sorted = false;
	bool running;
	
	//Selection sort
	void SelectionSortSetup();
	void SelectionSortRunFrame();
	std::vector<Block*>::iterator it_smallest;
	std::vector<Block*>::iterator it_toSort;
};


#endif // SORTER_H