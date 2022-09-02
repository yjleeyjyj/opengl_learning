#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Vertices, indices
GLfloat vertices[] =
{
	//         COORDINATES                       /      COLORS          //
	-0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f, // Lower left corner
	0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f, // Lower right corner
	0.0f,   0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,    0.9f, 0.45f, 0.17f, // Inner left
	0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,    0.9f, 0.45f, 0.17f, // Inner right
	0.0f,  -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f, // Inner down
};

GLuint indices[] =
{
	0, 3, 5,
	3, 2, 4,
	5, 4, 1,
};

int main(void)
{
	glfwInit();

	// Tell GLFW the Version of OpenGL, Which is the version of Itself: 3.3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW which OpenGL Profile prefer to Use: CORE profile.
	//
	// [NOTE]
	// Only 2 profiles exist.
	// - CORE : only contains Modern functions (GLFW_OPENGL_CORE_PROFILE)
	// - COMPATIBILITY : contains Modern and Outdated functions. (GLFW_OPENGL_COMPAT_PROFILE)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window Object
	// Parameter : Width, Height, Title, Use Full Screen , X(Don't Care)
	GLFWwindow* window = glfwCreateWindow(800, 800, "MyFirstOpenGL", NULL, NULL);
	// Quick Error Check
	if (window == NULL)
	{
		std::cout << "Failed to Create GLFW window" << std::endl;
		glfwTerminate();
		return -1; // check return code later
	}
	// Tell GLFW to show window object on screen
	glfwMakeContextCurrent(window);

	// <COLOR BACKGROUND>
	// Load GLAD to tell OpenGL preferenced Configurations
	gladLoadGL();

	// specify the viewport of OpenGL area of the window
	glViewport(0, 0, 800, 800); // top - left, bottom - right

	Shader shaderProgram("default.vert", "default.frag");
	
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Make Bigger or Smaller, scale manipulation
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Swap the Back Buffer with the front buffer 
	glfwSwapBuffers(window);

	// Continue Window Operation
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Specify the color of the Background
		glClear(GL_COLOR_BUFFER_BIT); // Clean the back buffer and assign the new color on it
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // repalce glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	// Cleaning Up Processes

	shaderProgram.Delete();
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
