#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class IndependentMesh : public Mesh
{
	public:
		/// <summary>
		/// Creates an Independent Mesh, a mesh that has its own Model Matrix with custom transformations attached to it.
		/// </summary>
		IndependentMesh();
		~IndependentMesh();

		/// <summary>
		/// Draw the mesh on screen.
		/// </summary>
		void RenderMesh();

		// drawType: GL_TRIANGLES, GL_LINES, GL_POINTS
		void RenderMesh(GLenum drawType);
		
		/// <summary>
		/// Draw the mesh on screen, combining its model matrix with a custom model matrix, specified in parameters.
		/// </summary>
		/// <param name="matrix">The matrix to apply to this mesh.</param>
		/// <param name="uniformModelLocation">The location of the matrix in the GPU.</param>
		void RenderMesh(glm::mat4& matrix, GLuint uniformModelLocation);

		/// <summary>
		/// Sets this mesh's custom model matrix.
		/// </summary>
		/// <param name="matrix">The matrix to be set.</param>
		/// <param name="uniformModelLocation">The location tied to the matrix.</param>
		void SetModelMatrix(glm::mat4& matrix, GLuint uniformModelLocation);
		glm::mat4& GetModelMatrix();
	private:
		/// <summary>
		/// The model matrix of this mesh.
		/// </summary>
		glm::mat4* modelMatrix;
		/// <summary>
		/// The location of the model matrix of this mesh.
		/// </summary>
		GLuint uniformModelLocation;
};

