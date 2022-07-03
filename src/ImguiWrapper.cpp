#include "ImguiWrapper.h"


//*Public

imguiWrapper::imguiWindow::imguiWindow(std::function<void(void)> windowFunction){
    this->windowFunction = windowFunction;
    shown = false;
}

imguiWrapper::imguiWrapper(){
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

imguiWrapper::~imguiWrapper(){
    Clean();
}

void imguiWrapper::imguiWindow::RenderWindow(){
    if(shown) windowFunction();
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
    DrawWindows();
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
    mainWindow = new imguiWindow(std::bind(&MainWindowFunction, this));
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
    mainWindow->RenderWindow();
}

void imguiWrapper::MainWindowFunction(){
    ImGui::ShowDemoWindow();
}

