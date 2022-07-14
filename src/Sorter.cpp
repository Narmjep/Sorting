#include "Sorter.h"
#include "Block.h"
#include <cmath>
#include <iostream>

Sorter::Sorter(int fps)
{
    this->fps = fps;
    running = sorted = false;
    algorithm = SelectionSort;
}

void Sorter::Setup(){
    switch(algorithm){
        case SelectionSort:
            SelectionSortSetup();
            break;
        case BubbleSort:
            BubbleSortSetup();
            break;
    };
}

void Sorter::RunSingleFrame(){
    switch(algorithm){
        case SelectionSort:
            SelectionSortRunFrame();
            break;
        case BubbleSort:
            BubbleSortRunFrame();
            break;
    };
}

void Sorter::Restart(){
    running = false;
    sorted = false;
}

void Sorter::SelectionSortSetup(){
    it_smallest = BlocksManager::blocks.begin();
    it_toSort = BlocksManager::blocks.begin();
}

void Sorter::SelectionSortRunFrame(){
    if(sorted) return;

    //Frames
    Uint64 FrameBegin = SDL_GetTicks64();
    //Find smallest
    for(std::vector<Block*>::iterator it = it_toSort; it != BlocksManager::blocks.end(); it++){
        Block* blockPtr_smallest = *it_smallest;
        Block* blockPtr_current = *it;

        if(blockPtr_current->height < blockPtr_smallest->height){
            //Move smallest to front
                //Swap indexes
            int index_smallest = blockPtr_smallest->index;
            int index_current = blockPtr_current->index;
            blockPtr_smallest->index = index_current;
            blockPtr_current-> index = index_smallest;
            std::iter_swap(it_smallest , it);
        }
    }
    //Find next smallest
    it_toSort++;
    it_smallest = it_toSort;
    //Check if END
    if(it_toSort == BlocksManager::blocks.end()){
        //Sorted!
        sorted = true;
        running = false;
        return;
    }
    //FPS
    if(fps == 0){
        return;
    }
    Uint64 FrameEnd = SDL_GetTicks64();
    float delay = FrameEnd - FrameBegin;
    SDL_Delay(floor(1000.0f/fps) - delay);

}

//*Bubble sort
void Sorter::BubbleSortSetup(){
    it_toSort = BlocksManager::blocks.begin();
}

void Sorter::BubbleSortRunFrame(){
    if(sorted) return;

     //Frames
    Uint64 FrameBegin = SDL_GetTicks64();

    static bool swapped_elements;
    //Compare two elements
    std::vector<Block*>::iterator it_next = std::next(it_toSort);
    if((*it_toSort)->height > (*it_next)->height ){
            //Swap indexes
            int index_next = (*std::next(it_toSort))->index;
            int index_current = (*it_toSort)->index;
            (*it_next)->index = index_current;
            (*it_toSort)-> index = index_next;
            std::iter_swap(it_toSort , it_next);
        swapped_elements = true;
    }
    //Increment
    it_toSort++;
    //Check if end
    if(it_toSort == std::prev(BlocksManager::blocks.end())){
        //End of array
        it_toSort = BlocksManager::blocks.begin();
        //Check if any elements had to be swapped
        if(!swapped_elements){
            //Sorted!
            sorted = true;
            running = false;
            return;
        }
        swapped_elements = false;
    }
    //FPS
    if(fps == 0){
        return;
    }
    Uint64 FrameEnd = SDL_GetTicks64();
    float delay = FrameEnd - FrameBegin;
    SDL_Delay(floor(1000.0f/fps) - delay);
}

