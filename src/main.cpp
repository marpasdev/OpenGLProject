#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include <GLFW/glfw3.h>  

#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>
#include <vector>

#include "models/tree.h"
#include "shader.h"
#include "shaderprogram.h"

#include <filesystem>   // testing

int main() {

	GLFWwindow* window;
	
	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	// Initialize GLAD and load OpenGL function pointers
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed\n");
		return -1;
	}

    float points[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint treeVBO = 0;
    glGenBuffers(1, &treeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);

    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, treeVBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

    std::cout << "Working directory: "
          << std::filesystem::current_path() << '\n';

std::cout << "Vertex exists: "
          << std::filesystem::exists("shaders/vertex/basic.vert") << '\n';

std::cout << "Fragment exists: "
          << std::filesystem::exists("shaders/fragment/basic.frag") << '\n';


    Shader vertexShader = Shader(GL_VERTEX_SHADER, "shaders/vertex/basic.vert");
    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");

    ShaderProgram program = ShaderProgram(vertexShader, fragmentShader);

    std::cout << "Program ID: " << program.getID() << "\n";

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.use();
        glBindVertexArray(VAO);

        // Draw a triangles
        // glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
        glDrawArrays(GL_TRIANGLES, 0, sizeof(tree) / (sizeof(float) * 6.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	// Get version info
	// printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	// printf("Vendor %s\n", glGetString(GL_VENDOR));
	// printf("Renderer %s\n", glGetString(GL_RENDERER));
	// printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	// int major, minor, revision;
	// glfwGetVersion(&major, &minor, &revision);
	// printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    return 0;
}