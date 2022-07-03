#ifndef IMGUIWRAPPER_H
#define IMGUIWRAPPER_H

#include <SDL.h>
#include <stdio.h>
#include <functional>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"


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
		imguiWindow(std::function<void(void)> windowFunction);
		std::function<void(void)> windowFunction;
		void RenderWindow();
		void Show();
		void Hide();
	private:
		bool shown;
	};
/* ---------------------------------------------- */
/* ---------- Declare you windows here ---------- */
/* ---------------------------------------------- */
	imguiWindow* mainWindow;
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

private:
	ImGuiIO* io;
	ImVec4 clear_color;
	void SetStyle(ImGuiStyle style);
	void CreateWindows();
	void DrawWindows();
	void Clean();
	/* ---------------------------------------------------------------------------------- */
	/*                              Window Functions	 							      */
	/* Write you IMGUI windows here starting with ImGui::Begin and ending with ImGui::End */
	/* ---------------------------------------------------------------------------------- */
	void MainWindowFunction();
};


#endif // IMGUIWRAPPER_H