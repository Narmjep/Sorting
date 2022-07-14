#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <filesystem>

//#define GET_CONSOLE // Alocates a console for debugging
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

    int nBlocks = 10;
    int fps = 10;

    //Init Libraries
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        const char* error = SDL_GetError();
        std::cerr << "Couldn't initialize SDL: " << error << std::endl;
        return 1;
    }
    IMGUI_CHECKVERSION();
    IMG_Init(~0);
    srand(time(NULL));

    //Create objects
    Sorter* sorter = new Sorter(fps);
    Renderer* renderer = new Renderer();
    BlocksManager* blocksManager = new BlocksManager(nBlocks, 50 , Renderer::windowHeight - 50);

    //Init objects
    renderer->Init(&(sorter->running));
    blocksManager->Init();
    sorter->Setup();
    renderer->gui->MainWindowInit(sorter , blocksManager);
    renderer->gui->mainWindow->Show();
    //Render loop
    while(renderer->running){
        //*Sorting
        if(sorter->running)sorter->RunSingleFrame();
        //*Rendering
        SDL_SetRenderDrawColor(Renderer::renderer, 0 , 0 , 0 , 255); // Draw black background
        renderer->Update();
    }

    //Cleaning
    delete renderer;
    delete blocksManager;
    delete sorter;
    SDL_Quit();

    return 0;
}
