#include "Block.h"
#include "SDL_image.h"
#include <iostream>

int BlocksManager::TotalBlocks;
std::vector<Block*> BlocksManager::blocks;
SDL_Texture* BlocksManager::blockTexture;

Block::Block(int index , int height)
{
    this->index = index;
    this->height = height;
}

void Block::Draw(){
    UpdatePosition();
    SDL_RenderCopy(Renderer::renderer , BlocksManager::blockTexture , NULL , &rect);
}

void Block::UpdatePosition(){
    this->rect.x = this->index*this->rect.w;
}

/////////////////////////////////////////////////////////

BlocksManager::BlocksManager(int n_blocks){
    TotalBlocks = n_blocks;
    for (int i = 0; i < TotalBlocks; i++){
        CreateBlock();
    }
    //Init Texture
    surface = IMG_Load(blockImgPath);
    if(!surface){std::cout << "IMG_Load failed: " << IMG_GetError() << std::endl;}
    blockTexture = SDL_CreateTextureFromSurface(Renderer::renderer, surface);
    SDL_FreeSurface(surface);
}

void BlocksManager::CreateBlock(){
    int height = rand() % maxHeight + minHeight;
    int newIndex = blocks.size();
    Block* block = new Block(newIndex , height);
    blocks.emplace_back(block);
    block->rect.w = Renderer::windowWidth / TotalBlocks;
    block->rect.y = Renderer::windowHeight - block->rect.h + heightOffset;
    block->rect.x = block->index*block->rect.w;
}

void BlocksManager::DrawBlocks(){
    SDL_SetRenderDrawColor(Renderer::renderer , 255, 255, 255 , 255);
    for(auto block : blocks){
        block->Draw();
    }
}