#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "ImguiWrapper.h"
#include "Sorter.h"

class imguiWrapper;
class Sorter;

class Renderer
{
public:
	SDL_Window* window;
	SDL_Event event;
	static SDL_Renderer* renderer;
	static int windowWidth, windowHeight;
	bool running;
	bool* isSorterRunning;
	imguiWrapper* gui;

	Renderer(Sorter* sorter);
	~Renderer();
	//Main Methodes 
	void Init(bool* isSorterRunning);
	void Update();
	void Destroy();

	//Other Methods
	void Render();
	void HandleEvents();

private:
	
};


#endif // RENDERER_H