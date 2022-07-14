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
	/**
	 * @brief Copies the block to the renderer.
	 * 
	 */
	void Draw();
	/**
	 * @brief Sets the block's position relative to its index in the set.
	 * 
	 */
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
	/**
	 * @brief Creates a set of Tiles.
	 * 
	 */
	void CreateSet();
	/**
	 * @brief Frees the current set.
	 * 
	 */
	static void DeleteCurrentSet();
	/**
	 * @brief Calls the Draw() method for every block in the current set.
	 * 
	 */
	static void DrawBlocks();

	//Debug
	/**
	 * @brief Prints the current set. Used for debugging only.
	 * 
 	*/
	static void GetBlocksArray();


private:
	SDL_Surface* surface;
	const char* blockImgPath = "block.png";
	void CreateBlock();
};

#endif // BLOCK_H