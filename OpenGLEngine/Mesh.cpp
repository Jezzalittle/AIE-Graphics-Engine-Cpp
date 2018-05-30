#include "Mesh.h"
#include <gl_core_4_4.h>
#include <glfw/glfw3.h>



void Mesh::initialiseQuad()
{

	// define 6 vertices's for 2 triangles
	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	vertices[0].texCoord = { 0, 1 }; // bottom left
	vertices[1].texCoord = { 1, 1 }; // bottom right
	vertices[2].texCoord = { 0, 0 }; // top left
	vertices[3].texCoord = { 0, 0 }; // top left
	vertices[4].texCoord = { 1, 1 }; // bottom right
	vertices[5].texCoord = { 1, 0 }; // top right
	initialiseBuffer(vertices);

	enableAttrib(0, 4, 0);
	enableAttrib(2, 2, 32);
	
	cleanUpBuffer();

	triCount = 2;

}

void Mesh::draw()
{
	glBindVertexArray(vao);
	// using induces or just vertices's?
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount,
			GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}




void Mesh::enableAttrib(int pos, int amount, int offset)
{
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, amount, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

}

void Mesh::initialiseBuffer(Vertex* vert)
{
	assert(vao == 0);

	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
		vert, GL_STATIC_DRAW);
}

void Mesh::cleanUpBuffer()
{
	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

}

