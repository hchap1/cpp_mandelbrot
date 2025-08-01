#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "shader.hpp"

class RenderLayer {
	public:
		RenderLayer(const char* vertexPath, const char* fragmentPath, std::vector<size_t> attributes)
		: shader(vertexPath, fragmentPath){

			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			unsigned int idx = 0;
			this -> vertexSize = 0;
			size_t vertexByteSize = 0;

			for (size_t attributeSize : attributes) {
				vertexByteSize += attributeSize * sizeof(float);
			}

			for (size_t attributeSize : attributes) {
				glVertexAttribPointer(
					idx,
					attributeSize,
					GL_FLOAT,
					GL_FALSE,
					vertexByteSize,
					(void*)((this -> vertexSize) * sizeof(float))
				);

				this -> vertexSize += attributeSize;
				glEnableVertexAttribArray(idx);
				idx ++;
			}
		}

		void set_vertices(float* vertices, size_t triangleCount) {
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(
				GL_ARRAY_BUFFER, 
				triangleCount * this -> vertexSize * 3 * sizeof(float),
				vertices, GL_STATIC_DRAW
			);
			this -> triangleCount = triangleCount;
		}

		void draw() {
			glBindVertexArray(vao);
			this -> shader.use();
			glDrawArrays(GL_TRIANGLES, 0, this -> triangleCount * 3);
		}

		void setFloat(const char* uniform, float value) {
			this -> shader.setFloat(uniform, value);
		}

	private:
		unsigned int vao;
		unsigned int vbo;
		size_t vertexSize;
		size_t triangleCount;
		Shader shader;
};
