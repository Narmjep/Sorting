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
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Makes the background of Imgui transparent
    bool use_work_area = true;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
    //*Window Functions
    MainWindowFunction(mainWindow);
    ImGui::PopStyleColor(); // Pop ImGuiCol_WindwowBg
}

/* -------------------------------------------------------------------------- */
/*                               Window Function                              */
/*                    Define you window functions here                        */
/* -------------------------------------------------------------------------- */

static bool mainWindowInit = false;
static Sorter* sorter_mainWindow;
static BlocksManager* blocksManager_mainWindow;

void imguiWrapper::MainWindowFunction(imguiWrapper::imguiWindow* mainWindow){

    //Variables
    static std::string Txt_startBtn = "Start";
    static bool lockSettings = false;
    static bool toggle_unlimitedFPS = false;
    static bool BtnClrPushed;
    //Lambda
    auto SetBtnColor = [](ImVec4 color){
        ImGui::PushStyleColor(ImGuiCol_Button , {0 , 1 , 0 , 1});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0 , 0.6f , 0 , 1));
        BtnClrPushed = true;
    };
    auto ResetBtnColor = []{
        ImGui::PopStyleColor(2);
        BtnClrPushed = false;
    };
    auto Refresh = []{
        lockSettings = false;
        //Create new tiles
        sorter_mainWindow->Restart();
        blocksManager_mainWindow->DeleteCurrentSet();
        blocksManager_mainWindow->CreateSet();
        sorter_mainWindow->Setup();
    };

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
    if(!lockSettings){
        if(ImGui::DragInt("Number of Tiles" , &BlocksManager::TotalBlocks , 0.3F  , 2 , 999)){
            Refresh();
        }
    }
    //Reset
    if(ImGui::Button("Refresh")){
        Refresh();
    }

    //*Algorithms
        //Selection Sort
            //Button Color
    if(sorter_mainWindow->algorithm == Sorter::SelectionSort){
        SetBtnColor({0,1,0,1});
    }
    bool btnPressed = false;
    if(!lockSettings)btnPressed = ImGui::Button("Selection sort");
    if(btnPressed){
        //Change the algorithm
        sorter_mainWindow->algorithm = Sorter::SelectionSort;
            //Setup new algorithm
        sorter_mainWindow->Setup();

        btnPressed = false;
    }
            //Reset Btn Color
    if(BtnClrPushed){
        ResetBtnColor();
    }
    if(!lockSettings)ImGui::SameLine();
        //Bubble sort
            //Btn Color
    if(sorter_mainWindow->algorithm == Sorter::BubbleSort){
        SetBtnColor(ImVec4(0,0.6,0,1));
    }
    if(!lockSettings) btnPressed = ImGui::Button("Bubble sort");
    if(btnPressed){
        //Change the algorithm
        sorter_mainWindow->algorithm = Sorter::BubbleSort;
            //Setup new algorithm
        sorter_mainWindow->Setup();

        btnPressed = false;
    }
            //Reset Btn Color
    if(BtnClrPushed){
        ResetBtnColor();
    }
    //Start Btn
    if(ImGui::Button(Txt_startBtn.c_str())){
        sorter_mainWindow->running = !sorter_mainWindow->running;
        if(sorter_mainWindow->running){
            lockSettings = true;
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


