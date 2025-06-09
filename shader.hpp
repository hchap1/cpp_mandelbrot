#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>

class Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath) {

			unsigned int vertexShader;
			unsigned int fragmentShader;

			std::ifstream vertexFile(vertexPath, std::ios::binary | std::ios::ate);
			if (!vertexFile) {
				throw std::runtime_error("vertexShader did not exist at specified location.");
			}
			std::streamsize vertexSize = vertexFile.tellg();
			vertexFile.seekg(0, std::ios::beg);

			std::unique_ptr<char[]> vertexBuffer(new char[vertexSize + 1]);
			vertexBuffer[vertexSize] = '\0';
			if (!vertexFile.read(vertexBuffer.get(), vertexSize)) {
				throw std::runtime_error("vertexShader unreadable.");
			}

			std::ifstream fragmentFile(fragmentPath, std::ios::binary | std::ios::ate);
			if (!fragmentFile) {
				throw std::runtime_error("fragmentShader did not exist at specified location.");
			}
			std::streamsize fragmentSize = fragmentFile.tellg();
			fragmentFile.seekg(0, std::ios::beg);

			std::unique_ptr<char[]> fragmentBuffer(new char[fragmentSize + 1]);
			fragmentBuffer[fragmentSize] = '\0';
			if (!fragmentFile.read(fragmentBuffer.get(), fragmentSize)) {
				throw std::runtime_error("fragmentShader unreadable.");
			}

			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexSource(vertexBuffer.get(), vertexSize);
			const char* vertexSourcePtr = vertexSource.c_str();
			glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
			glCompileShader(vertexShader);

			int vertexSuccess;
			char vertexInfoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);

			if (!vertexSuccess) {
				glGetShaderInfoLog(vertexShader, 512, NULL, vertexInfoLog);
				std::cout << "Vertex Shader failed to compile." << std::endl << vertexInfoLog << std::endl;
			}

			std::string fragmentSource(fragmentBuffer.get(), fragmentSize);
			const char* fragmentSourcePtr = fragmentSource.c_str();
			glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
			glCompileShader(fragmentShader);

			int fragmentSuccess;
			char fragmentInfoLog[512];
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);

			if (!fragmentSuccess) {
				glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentInfoLog);
				std::cout << "Fragment Shader failed to compile." << std::endl << fragmentInfoLog << std::endl;
			}

			this -> shaderID = glCreateProgram();
			glAttachShader(this -> shaderID, vertexShader);
			glAttachShader(this -> shaderID, fragmentShader);
			glLinkProgram(this -> shaderID);

			int programSuccess;
			char programInfoLog[512];
			glGetProgramiv(this -> shaderID, GL_LINK_STATUS, &programSuccess);

			if(!programSuccess) {
				glGetProgramInfoLog(this -> shaderID, 512, NULL, programInfoLog);
				std::cout << "Shader failed to compile." << std::endl << programInfoLog << std::endl;
			}

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		void use() {
			glUseProgram(this -> shaderID);
		}

	private:
		unsigned int shaderID;
};
