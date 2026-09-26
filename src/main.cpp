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

int main() {

	GLFWwindow* window;
	
	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	//Initialization of a specific version
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/


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

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

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