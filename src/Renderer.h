#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

class Renderer
{
public:
	static SDL_Renderer* renderer;
	static int windowWidth, windowHeight;
	bool running;

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
	SDL_Window* window;
	SDL_Event event;
};


#endif // RENDERER_H