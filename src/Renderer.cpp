#include "Renderer.h"
#include "Block.h"

SDL_Renderer* Renderer::renderer;
int Renderer::windowWidth = 1280;
int Renderer::windowHeight = 720;

Renderer::Renderer()
{
}

Renderer::~Renderer(){
    Destroy();
}

void Renderer::Init(){
    window = SDL_CreateWindow("My Window",SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , windowWidth , windowHeight , 0);
	Renderer::renderer = SDL_CreateRenderer(window , -1 , 0);
    running = true;
}

void Renderer::Update(){
    HandleEvents();
    Render();
}

void Renderer::Destroy(){
    SDL_DestroyRenderer(Renderer::renderer);
    SDL_DestroyWindow(window);
}

void Renderer::Render(){
    SDL_RenderClear(Renderer::renderer);
    BlocksManager::DrawBlocks();
    SDL_RenderPresent(Renderer::renderer);
}

void Renderer::HandleEvents(){
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            running = false;
    }
}
