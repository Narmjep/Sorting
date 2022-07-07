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
	imguiWindow* mainWindow;
/* ---------------------------------------------- */
/* ---------- Declare you windows here ---------- */
/* ---------------------------------------------- */
	//Methods
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
	void SetStyle(ImGuiStyle style);
	void CreateWindows();
	void Clean();
	/* ---------------------------------------------------------------------------------- */
	/*                              Window Functions	 							      */
	/* Declare your IMGUI windows here starting with ImGui::Begin and ending with ImGui::End */
	/* ---------------------------------------------------------------------------------- */
	static void MainWindowFunction(imguiWindow* mainWindow);
};


#endif // IMGUIWRAPPER_H