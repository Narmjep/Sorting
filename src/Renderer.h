#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "ImguiWrapper.h"

class Renderer
{
public:
	SDL_Window* window;
	SDL_Event event;
	static SDL_Renderer* renderer;
	static int windowWidth, windowHeight;
	bool running;
	imguiWrapper* gui;

	Renderer();
	~Renderer();
	//Main Methodes 
	void Init();
	void Update();
	void Destroy();

	//Other Methods
	void Render();
	void HandleEvents();

private:
	
};


#endif // RENDERER_H