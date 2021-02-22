// Modified from https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/* Entire process of creating a vertex and fragment shader from source code on disk, compiling them and then creating and linking a program*/
class Shader
{
public:
	unsigned int ID;

	/// <summary>
	/// Constructor, constructs shaders from file
	/// </summary>
	/// <param name="vertexPath"></param>
	/// <param name="fragmentPath"></param>
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void free(); // free program
	unsigned int getId();

	/// <summary>
	/// Used to set a boolean uniform inside a shader
	/// </summary>
	/// <param name="name">Name of the uniform to be set</param>
	/// <param name="value">Boolean value to be set</param>
	void setBool(const std::string& name, bool value) const;
	/// <summary>
	/// Used to set an integer uniform inside a shader
	/// </summary>
	/// <param name="name">Name of the uniform to be set</param>
	/// <param name="value">Integer value to be set</param>
	void setInt(const std::string& name, int value) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void setFloat(const std::string& name, float value) const;
	/// <summary>
	/// Used to set a 4x4 matrix uniform inside a shader
	/// </summary>
	/// <param name="name">Name of the uniform to be set</param>
	/// <param name="transformMatrix">4x4 matrix to be set</param>
	void setMatrix4Float(const std::string& name, glm::mat4* transformMatrix) const;
	/// <summary>
	/// Retrieves the location for a uniform from the shader
	/// </summary>
	/// <param name="name">Name of the uniform</param>
	/// <returns>Returns the unsigned integer that points to that uniform</returns>
	GLuint getLocation(const std::string& name) const;
};
