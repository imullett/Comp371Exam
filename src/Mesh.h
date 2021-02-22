// Modified from Ben Cook's Udemy OpenGL course https://www.udemy.com/course/graphics-with-modern-opengl/
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh
{
	public:
		Mesh();
		~Mesh();

		/// <summary>
		/// Creates a mesh using the supplied parameters
		/// </summary>
		/// <param name="vertices">Pointer to the vertices of the mesh.</param>
		/// <param name="indices">Pointer to the indices for index drawing of the mesh.</param>
		/// <param name="numOfVertices">Number of vertices</param>
		/// <param name="numOfIndices">Number of indices in the index drawing array</param>
		void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
		/// <summary>
		/// Draws the mesh on screen
		/// </summary>
		virtual void RenderMesh();
		
		// drawType: GL_TRIANGLES, GL_LINES, GL_POINTS
		virtual void RenderMesh(GLenum drawType);
		/// <summary>
		/// Draws the mesh on screen using a custom transformation
		/// </summary>
		/// <param name="matrix">The model matrix, representing the transformation to apply.</param>
		/// <param name="uniformModelLocation">The location of the provided model matrix.</param>
		virtual void RenderMesh(glm::mat4& matrix, GLuint uniformModelLocation);
		
		/// <summary>
		/// Clears the mesh from the GPU.
		/// </summary>
		void ClearMesh();


	protected:
		GLuint VAO, VBO, IBO;
		GLsizei indexCount; // Just an integer, but recognized by openGL to represent a size.
};

