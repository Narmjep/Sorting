#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <string>
#include "Block.h"

class Block;

class Sorter
{
public:
	Sorter(int fps);
	~Sorter() = default;

	enum Algorithm{
		SelectionSort,
		BubbleSort,
	};

	Algorithm algorithm;

	//general
	int fps = 0;
	bool running;
	bool sorted;
	
	void Setup();
	void RunSingleFrame();
	void Restart();

private:
	//Common
	std::vector<Block*>::iterator it_toSort;
	
	//Selection sort
	void SelectionSortSetup();
	void SelectionSortRunFrame();
	std::vector<Block*>::iterator it_smallest;

	//Bubble sort
	void BubbleSortSetup();
	void BubbleSortRunFrame();
	
};


#endif // SORTER_H