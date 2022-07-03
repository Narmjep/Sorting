#include "Renderer.h"
#include "Block.h"
#include "imguiWrapper.h"
#include <iostream>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

SDL_Renderer* Renderer::renderer;
int Renderer::windowWidth = 1280;
int Renderer::windowHeight = 720;

Renderer::Renderer()
{
    gui = new imguiWrapper();
}

Renderer::~Renderer(){
    Destroy();
}

void Renderer::Init(){
    //Create widnow
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("My Window",SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , windowWidth , windowHeight , window_flags);
    //Create Renderer
    Renderer::renderer = SDL_CreateRenderer(window , -1 , SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    running = true;
    //Initialize gui
    gui->Init(window , renderer);
}

void Renderer::Update(){
    HandleEvents();
    Render();
}

void Renderer::Destroy(){
    delete gui;
    SDL_DestroyRenderer(Renderer::renderer);
    SDL_DestroyWindow(window);
}

void Renderer::Render(){
    gui->StartFrame();
    gui->RenderFrame();
    SDL_RenderClear(Renderer::renderer);
    BlocksManager::DrawBlocks();
    gui->RenderData();
    SDL_RenderPresent(Renderer::renderer);
}

void Renderer::HandleEvents(){
    while(SDL_PollEvent(&event)){
        gui->HandleEvents(&event);
        switch(event.type){
            case SDL_QUIT:
                running = false;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)){
                    running = false;
                }
        }
    }
}
