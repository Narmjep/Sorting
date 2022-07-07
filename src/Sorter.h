#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include "Block.h"

class Block;

class Sorter
{
public:
	Sorter(int fps);
	~Sorter() = default;

	//general
	int fps = 0;
	bool running;
	bool sorted;
	
	void Restart();
	void Pause();

	//Selection sort
	void SelectionSortSetup();
	void SelectionSortRunFrame();
	std::vector<Block*>::iterator it_smallest;
	std::vector<Block*>::iterator it_toSort;
};


#endif // SORTER_H