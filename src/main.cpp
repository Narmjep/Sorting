#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <filesystem>
#define GET_CONSOLE
#ifdef GET_CONSOLE
#include <windows.h>
#endif

#include "Renderer.h"
#include "Block.h"
#include "Sorter.h"
#include "imguiWrapper.h"



int main(int argc, char **argv){
    //Init
    #ifdef GET_CONSOLE
    AllocConsole();
    FILE * f;
    freopen_s(&f , "CONOUT$" , "w" , stdout);
    freopen_s(&f , "CONOUT$" , "w" , stdin);
    freopen_s(&f , "CONOUT$" , "w" , stderr);
    #endif

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        const char* error = SDL_GetError();
        std::cerr << "Couldn't initialize SDL: " << error << std::endl;
        return 1;
    }
    IMGUI_CHECKVERSION();
    IMG_Init(~0);
    srand(time(NULL));
    Renderer* renderer = new Renderer();

    //Handle arguments
    int nBlocks = 10;
    int fps = 10;

    if(argc > 1){
        int n = atoi(argv[1]);
        if(n) nBlocks = n;
    }

    if(argc >= 2){
        int n = atoi(argv[2]);
        if(n) fps = n;
    }

    //Start
    renderer->Init();
    BlocksManager* blocksManager = new BlocksManager(nBlocks);
    Sorter* sorter = new Sorter(fps);
    sorter->SelectionSortSetup();
    sorter->running = true;
    renderer->gui->mainWindow->Show();
    //Game loop
    while(renderer->running){
        //*Sorting
        if(sorter->running)sorter->SelectionSortRunFrame();
        //*Rendering
        SDL_SetRenderDrawColor(Renderer::renderer, 0 , 0 , 0 , 255);
        renderer->Update();
    }

    //Cleaning
    delete renderer;
    delete blocksManager;
    SDL_Quit();


    return 0;
}
