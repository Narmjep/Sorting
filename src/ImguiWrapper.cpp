#include "ImguiWrapper.h"
#include <iostream>

//*Public

imguiWrapper::imguiWindow::imguiWindow(ImGuiWindowFlags flags){
    shown = false;
    this->flags = flags;
}

imguiWrapper::imguiWrapper(){
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

imguiWrapper::~imguiWrapper(){
    Clean();
}


void imguiWrapper::imguiWindow::Show(){
    shown = true;
}

void imguiWrapper::imguiWindow::Hide(){
    shown = false;
}

bool imguiWrapper::Init(SDL_Window* window , SDL_Renderer* renderer){
    
    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    SetStyle(imguiWrapper::ImGuiStyle::classic);
    //Implementation
    if(!ImGui_ImplSDL2_InitForSDLRenderer(window , renderer)) return false;
    if(!ImGui_ImplSDLRenderer_Init(renderer)) return false;
    //imguiWindows
    CreateWindows();
    //Success
    return true;
}

void imguiWrapper::HandleEvents(SDL_Event* event){
    ImGui_ImplSDL2_ProcessEvent(event);
}

void imguiWrapper::StartFrame(){
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void imguiWrapper::RenderFrame(){
    ImGui::Render();
}

void imguiWrapper::RenderData(){
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void imguiWrapper::Clean(){
    this->DestroyWindows();
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
}

void imguiWrapper::CreateWindows(){
    /* -------------------------------------------------------------------------- */
    /*                           Create your windows here                         */
    /* -------------------------------------------------------------------------- */
    mainWindow = new imguiWindow(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
}

void imguiWrapper::DestroyWindows(){
    delete mainWindow;
}


//*Private

void imguiWrapper::SetStyle(ImGuiStyle style){
    switch(style){
        case classic:
            ImGui::StyleColorsClassic();
            break;
        case dark:
            ImGui::StyleColorsDark();
            break;
        case light:
            ImGui::StyleColorsLight();
            break;
    }
}

void imguiWrapper::DrawWindows(){
    //*ImGUi Setup
    //Background
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    bool use_work_area = true;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
    //*Window Function
    MainWindowFunction(mainWindow);
    ImGui::PopStyleColor();
}

/* -------------------------------------------------------------------------- */
/*                               Window Function                              */
/*                    Define you window functions here                        */
/* -------------------------------------------------------------------------- */
static std::string Txt_startBtn = "Start";
static bool lockNTiles = false;
static bool mainWindowInit = false;
static bool toggle_unlimitedFPS = false;
static Sorter* sorter_mainWindow;
static BlocksManager* blocksManager_mainWindow;



void imguiWrapper::MainWindowFunction(imguiWindow* mainWindow){
    //Check if initialized
    if(!mainWindowInit){
        std::cerr << "Window has not been initialized" << std::endl;
        return;
    }
    ImGui::Begin(" " , &(mainWindow->shown) , mainWindow->flags);
    ImGui::SameLine();
    //FPS
    ImGui::Checkbox("Unlimited FPS" , &toggle_unlimitedFPS);
    if(!toggle_unlimitedFPS){
        ImGui::DragInt("FPS" , &(sorter_mainWindow->fps) , 0.2F  , 1 , 300);
    } else {
        //Unlimited FPS
        sorter_mainWindow->fps = 0;
    }
    //N Tiles
    if(!lockNTiles) ImGui::DragInt("Number of Tiles" , &BlocksManager::TotalBlocks , 0.3F  , 2 , 999);
    //Reset
    if(ImGui::Button("Refresh")){
        lockNTiles = false;
        //Create new tiles
        sorter_mainWindow->Restart();
        blocksManager_mainWindow->DeleteCurrentSet();
        blocksManager_mainWindow->CreateSet();
        sorter_mainWindow->SelectionSortSetup();
    }
    //Start Btn
    if(ImGui::Button(Txt_startBtn.c_str())){
        sorter_mainWindow->running = !sorter_mainWindow->running;
        if(sorter_mainWindow->running){
            lockNTiles = true;
        } 
    }
    if(sorter_mainWindow->running){
        Txt_startBtn = "Stop";
    } else {
        Txt_startBtn = "Start";
    }
    ///////

    ImGui::End();
}

void imguiWrapper::MainWindowInit(Sorter* sorter , BlocksManager* blocksManager){
    sorter_mainWindow = sorter;
    blocksManager_mainWindow = blocksManager;
    mainWindowInit = true;
}

