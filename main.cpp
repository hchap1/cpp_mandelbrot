#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "window.hpp"
#include "rendering.hpp"

int main() {

	Window window = Window(1000, 1000, "Test");
	RenderLayer test = RenderLayer("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl", { 2 });

	float vertices[] = {
		-1.0f, -1.0f,
		-1.0f,  1.0f,
		 1.0f,  1.0f,

		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f
	};  

	test.set_vertices(vertices, 2);

	while (window.running()) {
		window.clear_screen(135, 206, 235);
		test.draw();
		window.update();
	}

    glfwTerminate();
    return 0;
}
