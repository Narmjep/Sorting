#include "ImguiWrapper.h"
#include <iostream>

//*Public

imguiWrapper::imguiWindow::imguiWindow(ImGuiWindowFlags flags){
    shown = false;
    this->flags = flags;
}

imguiWrapper::imguiWrapper(Sorter* sorter){
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    this->sorter = sorter;
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
    MainWindowFunction(mainWindow , sorter);
    ImGui::PopStyleColor();
}

/* -------------------------------------------------------------------------- */
/*                               Window Function   
/*                    Define you window functions here                        */
/* -------------------------------------------------------------------------- */

void imguiWrapper::MainWindowFunction(imguiWindow* mainWindow , Sorter* sorter){
    ImGui::Begin(" " , &(mainWindow->shown) , mainWindow->flags);
    ImGui::Text("Hello world!");
    ImGui::DragInt("FPS" , &(sorter->fps) , 1.0F  , 1 , 300); 
    if(ImGui::Button("START")){
        std::cout << "pressed";
        sorter->running = !sorter->running;
    }
    ImGui::End();

}

