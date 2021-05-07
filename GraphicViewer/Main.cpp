#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Libraries/include/stb_image/stb_image.h"

int main()
{
	// Initialize GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using. Here we use 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFWWindow object of 800x800 pixels
	GLFWwindow* window = glfwCreateWindow(800,800,"Graphic Viewer",NULL,NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	// Introduce the window to the current context
	glfwMakeContextCurrent(window);
	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewpoint of OpenGL in the Window. 
	glViewport(0,0,800,800);
	// Specify the color of the background
	glClearColor(0.07f,0.13f,0.17f,1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Specifying the vertex positions
	/*
	float vertices[] =
	{
		-0.5f   , -0.5f * float(sqrt(3)) /     3,  0.8f, 0.3f,  0.02f,
		 0.5f   , -0.5f * float(sqrt(3)) /     3, 0.8f, 0.3f,  0.02f,
		 0.0f   ,  0.5f * float(sqrt(3)) * 2 / 3, 0.8f, 0.3f,  0.02f,

		-0.5 / 2,  0.5f * float(sqrt(3)) / 6    , 0.9f, 0.45f, 0.17f,
		 0.5 / 2,  0.5f * float(sqrt(3)) / 6    , 0.9f, 0.45f, 0.17f,
		 0.0 / 2, -0.5f * float(sqrt(3)) / 3    , 0.9f, 0.45f, 0.17f,

		 -1.0f  ,                         0.0f  , 0.9f, 0.45f, 0.17f,
		 -0.5f  ,                         1.0f  , 0.8f, 0.3f,  0.02f,
		  0.0f  ,                         0.0f  , 0.8f, 0.3f,  0.02f,
		  0.5f  ,                        -1.0f  , 0.8f, 0.3f,  0.02f,
		  1.0f  ,                         0.0f  , 0.8f, 0.3f,  0.02f,
	};
	unsigned int indices[] = {
		6,7,8,
		8,9,10,
		0,3,5,
		3,2,4,
		5,4,1
	};
	*/
	// Vertices coordinates
	float vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};

	// Indices for vertices order
	unsigned int indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};

	// Pipeline Starts Here (Shaders)
	Shader shader("resources/shaders/Basic.shader");
	shader.Bind();
	// Vertex Buffer
	VertexBuffer vb(vertices, sizeof(vertices));
	// Vertex Array Object
	VertexArray vao(3); //x,y,z, color coordinate per vertex location attrib and color attrib
	//Index Buffer 
	IndexBuffer ib(indices,sizeof(indices));

	// Unbinding everything
	glBindVertexArray(0);
	shader.Unbind();
	vb.Unbind();
	ib.Unbind();
	vao.Unbind();

	// Adding textures
	Texture texture("resources/textures/Untitled.png");

	glfwSwapInterval(1); //Sync with monitors refresh rate
	// Main while loop
	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		// Setting up uniforms
		shader.setUniform1f("scale", 0.5f);
		shader.setUniform1i("tex0", 0);
		texture.Bind();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // DrawCall

		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		
	}


	// Delete the window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}


// https://www.youtube.com/watch?v=45MIykWJ-C4&list=WL&index=35 46:35