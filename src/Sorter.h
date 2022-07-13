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
	//Number of available algorithms Make sure this is set correctly!
	static const int nAlgorithms = 2;
	class Number_Of_Algorithms_Exception : public std::exception{
	public:
		std::string what(){
			return "Number of algorithms exception! Make sure you set a name for every algorithm in ImguiWrapper.cpp and that the static const int nAlgorithms in Sorter.h is set correctly.\n";
		}
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