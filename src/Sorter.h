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
	/**
	 * @brief Sets up the algorithm. Call before runnig the Sorter.
	 * 
	 */
	void Setup();
	/**
	 * @brief Runs a single sorting frame. Each frame corresponds to one element being swapped.
	 * 
	 */
	void RunSingleFrame();
	/**
	 * @brief Resets the sorter.
	 * 
	 */
	void Restart();

private:
	//Common
	std::vector<Block*>::iterator it_toSort;
	
	//Selection sort
	/**
	 * @brief Sets up the selection sort algorithm. Read the Sorter::Setup documentation.
	 * 
	 */
	void SelectionSortSetup();
	/**
	 * @brief Sets up the selection sort algorithm. Read the Sorter::RunSingleFrame documentation.
	 * 
	 */
	void SelectionSortRunFrame();
	std::vector<Block*>::iterator it_smallest;

	//Bubble sort
	/**
	 * @brief Sets up the bubble sort algorithm. Read the Sorter::Setup documentation.
	 * 
	 */
	void BubbleSortSetup();
	/**
	 * @brief Sets up the bubble sort algorithm. Read the Sorter::RunSingleFrame documentation.
	 * 
	 */
	void BubbleSortRunFrame();
	
};


#endif // SORTER_H