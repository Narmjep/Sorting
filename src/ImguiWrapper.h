#ifndef IMGUIWRAPPER_H
#define IMGUIWRAPPER_H

#include <SDL.h>
#include <stdio.h>
#include <functional>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "Sorter.h"
#include "Block.h"

class Sorter;
class BlocksManager;

class imguiWrapper
{
public:
	enum ImGuiStyle {
		classic,
		dark,
		light
	};
	class imguiWindow{
	public:
		imguiWindow(ImGuiWindowFlags flags);
		void Show();
		void Hide();
		bool shown;
		ImGuiWindowFlags flags;
	};
	/* ---------------------------------------------- */
	/* ---------- Declare you windows here ---------- */
	/* ---------------------------------------------- */
	imguiWindow* mainWindow;

	//*Methods
	imguiWrapper();
	~imguiWrapper();
	/**
	 * @brief Initializes Imgui. Call after creating the renderer.
	 * 
	 * @param window SDL_window* window you want to attach the gui to
	 * @param renderer SDL_Renderer* used for rendering in your application.
	 * @return true if initialization succeeded, false if initialization failed.
	 */
	bool Init(SDL_Window* window , SDL_Renderer * renderer);
	/**
	 * @brief Handles SDL events. Call inside while(SDL_PollEvent()).
	 * 
	 * @param event A pointer to the SDL_event used for handling events
	 */
	void HandleEvents(SDL_Event* event);
	/**
	 * @brief Creates a new frame. Call before RenderFrame().
	 * 
	 */
	void StartFrame();
	/**
	 * @brief Draws the imguiWindows. Call after creating a new frame and before rendering that frame. 
	 * 
	 */
	void DrawWindows();
	/**
	 * @brief Calls ImGui::Render(). Call before SDL_RenderClear();
	 * 
	 */
	void RenderFrame();
	/**
	 * @brief Call before SDL_RenderPresent();
	 * 
	 */
	void RenderData();
	/**
	 * @brief Deletes the imguiWindows.
	 * 
	 */
	void DestroyWindows();

	//Window Init Fucntions
	static void MainWindowInit(Sorter* sorter , BlocksManager* blocksManager);

private:
	ImGuiIO* io;
	ImVec4 clear_color;
	/**
	 * @brief Set the ImGui Style.
	 * 
	 * @param style ImguiWrapper::ImGuiStyle you want to use. 
	 */
	void SetStyle(ImGuiStyle style);
	/**
	 * @brief Create the imguiWindow objects
	 * 
	 */
	void CreateWindows();
	void Clean();
	/* ---------------------------------------------------------------------------------- */
	/*                              Window Functions	 							      */
	/* Declare your IMGUI windows here starting with ImGui::Begin and ending with ImGui::End */
	/* ---------------------------------------------------------------------------------- */
	
	/**
	 * @brief The window function defining your window and its UI elemtns. Starts with ImGui::Begin and ends with ImGui::End()
	 * 
	 * @param mainWindow ImguiWrapper::imguiWindow object corresponding to the window.
	 */
	static void MainWindowFunction(imguiWindow* mainWindow);
};


#endif // IMGUIWRAPPER_H