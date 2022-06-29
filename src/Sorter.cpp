#include "Sorter.h"
#include "Block.h"
#include <cmath>

Sorter::Sorter(int fps)
{
    this->fps = fps;
}

void Sorter::SelectionSortSetup(){
    it_smallest = BlocksManager::blocks.begin();
    it_toSort = BlocksManager::blocks.begin();
}

void Sorter::SelectionSortRunFrame(){
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
    if(it_toSort == BlocksManager::blocks.end()) running = false;
    //
    Uint64 FrameEnd = SDL_GetTicks64();
    float delay = FrameEnd - FrameBegin;
    SDL_Delay(floor(1000.0f/fps) - delay);

}
