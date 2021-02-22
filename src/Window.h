// Modified from Ben Cook's Udemy OpenGL course https://www.udemy.com/course/graphics-with-modern-opengl/
#pragma once

#include "stdio.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:

	/// <summary>
	/// Create a window object
	/// </summary>
	Window();

	/// <summary>
	/// Create a window object with a specific width and height
	/// </summary>
	/// <param name="windowWidth">Window width.</param>
	/// <param name="windowHeight">Window height.</param>
	Window(GLint windowWidth, GLint windowHeight);

	/// <summary>
	/// Initialize the window
	/// </summary>
	int initialise();

	/// <summary>
	/// Gets the buffer width
	/// </summary>
	/// <returns>A GLint representing the buffer width</returns>
	GLint getBufferWidth() { return bufferWidth; }
	/// <summary>
	/// Gets the buffer height
	/// </summary>
	/// <returns>A GLint representing the buffer height</returns>
	GLint getBufferHeight() { return bufferHeight; }

	/// <summary>
	/// Determines whether or not the window should stay open
	/// </summary>
	/// <returns>A boolean</returns>
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	/// <summary>
	/// Gets the array of keys
	/// </summary>
	/// <returns>An array of booleans</returns>
	bool* getKeys() { return keys;  }

	/// <summary>
	/// Gets the change in mouse position on the x-axis
	/// </summary>
	/// <returns>A GLfloat</returns>
	GLfloat getDeltaX() const { return deltaX; }
	/// <summary>
	/// Gets the change in mouse position on the y-axis
	/// </summary>
	/// <returns>A GLfloat</returns>
	GLfloat getDeltaY() const { return deltaY; }

	/// <summary>
	/// Calls glfwSwapBuffers
	/// </summary>
	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	///<summary>
	/// Deconstructor
	/// </summary>
	~Window();

private:
	/// <summary>
	/// The main window
	/// </summary>
	GLFWwindow * mainWindow;

	/// <summary>
	/// The window's width
	/// </summary>
	GLint width;
	/// <summary>
	/// The window's height
	/// </summary>
	GLint height;
	
	/// <summary>
	/// The buffer's width
	/// </summary>
	GLint bufferWidth;
	/// <summary>
	/// The buffer's height
	/// </summary>
	GLint bufferHeight;

	/// <summary>
	/// A boolean array of keyboard and mouse buttons. When a button is pressed, its associated array element will become true
	/// </summary>
	bool keys[1024];

	/// <summary>
	/// Last position of the mouse on the x-axis
	/// </summary>
	GLfloat lastX;
	/// <summary>
	/// Last position of the mouse on the y-axis
	/// </summary>
	GLfloat lastY;
	/// <summary>
	/// The change in the mouse's position on the x-axis
	/// </summary>
	GLfloat deltaX;
	/// <summary>
	/// The change in the mouse's position on the y-axis
	/// </summary>
	GLfloat deltaY;

	/// <summary>
	/// Whether or not the mouse has moved yet
	/// </summary>
	bool initialMouseMove;

	/// <summary>
	/// Callback function to handle key presses
	/// </summary>
	/// <param name="window">The window</param>
	/// <param name="key">The key pressed</param>
	/// <param name="code"></param>
	/// <param name="action">Whether the key was pressed or released</param>
	/// <param name="mode"></param>
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	/// <summary>
	/// Callback function to handle mouse movement
	/// </summary>
	/// <param name="window">The window</param>
	/// <param name="x">The x-coordinate of the mouse's position</param>
	/// <param name="y">The x-coordinate of the mouse's position</param>
	static void handleMouse(GLFWwindow* window, double x, double y);
	/// <summary>
	/// Callback function to handle mouse presses
	/// </summary>
	/// <param name="window">The window</param>
	/// <param name="button">The button pressed</param>
	/// <param name="action">Whether the key was pressed or released</param>
	/// <param name="mods"></param>
	static void handleMouseButtons(GLFWwindow* window, int button, int action, int mods);
	/// <summary>
	/// Calls all callback functions
	/// </summary>
	void createCallbacks();
};
