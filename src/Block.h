#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <SDL.h>
#include <cstdlib>
#include <memory>

#include "Renderer.h"

class Renderer;

class Block
{
public:
	int& height = rect.h;
	int index;
	SDL_Rect rect;

	Block(int index , int height);
	~Block() = default;

	void Draw();
	void UpdatePosition();
	
};

class BlocksManager
{
public:
	BlocksManager(int n_blocks , int minHeight , int maxHeight);
	~BlocksManager()=default;
	int minHeight;
	int maxHeight;
	int heightOffset = 20;
	static int TotalBlocks;
	static SDL_Texture* blockTexture;
	static std::vector<Block*> blocks;

	void Init();
	void CreateSet();
	static void DeleteCurrentSet();
	static void DrawBlocks();

private:
	SDL_Surface* surface;
	const char* blockImgPath = "block.png";
	void CreateBlock();
};

#endif // BLOCK_H