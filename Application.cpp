#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "spdlog/spdlog.h"

#include <string>
#include <iostream>


GLFWwindow* createWindow(const char* title, int width = 1280, int height = 720)
{
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to open GLFW window.\n";
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW cannot be initialized!\n";
		return nullptr;
	}

	return window;
}

int main()
{
	std::cout << "Hello OpenGL!" << std::endl;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	GLFWwindow* window = createWindow("OpenGL Boilerplate", 900, 600);
	if (window == nullptr)
		return -1;

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

	// Spdlog Example
	spdlog::info("Welcome to spdlog!");
	spdlog::error("Some error message with arg: {}", 1);

	//Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.2f, 0.8f, 1.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Text("Hello OpenGL from ImGui!");

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	return 0;
}
