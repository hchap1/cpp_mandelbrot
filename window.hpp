#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>

class Window {
	public:
		Window(size_t width, size_t height, const char* name) {

			if (!glfwInit()) {
				std::cerr << "[WINDOW] Failed to initialize GLFW" << std::endl;
				glfwTerminate();
				exit(-1);
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			this -> window = glfwCreateWindow(width, height, name, NULL, NULL);

			// Attempt to create the window
			if (!this -> window) {
				std::cerr << "[WINDOW] Failed to create window." << std::endl;
				glfwTerminate();
				exit(-1);
			}

			// Make this the current context
			glfwMakeContextCurrent(window);

			if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
				std::cerr << "Failed to initialize GLAD\n";
				glfwTerminate();
				exit(-1);
			}

			glfwSetWindowUserPointer(window, this);
			glViewport(0, 0, width, height);

			const GLubyte* version = glGetString(GL_VERSION);
			std::cout << "OpenGL version: " << version << std::endl;
		}

		bool running() {
			return !glfwWindowShouldClose(this -> window);
		}

		void clear_screen(uint8_t r, uint8_t g, uint8_t b) {
			glClearColor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void update() {
			glfwSwapBuffers(this -> window);
			glfwPollEvents();
		}

	private:
		GLFWwindow* window;
};
