#pragma once
#include <glm\ext.hpp>
#include <glm\glm.hpp>

class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {};

	virtual ~Mesh();
	
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void initialiseQuad();

	virtual void draw();


private:

	void enableAttrib(int pos, int amount, int offset);
	void initialiseBuffer(Vertex* vert);
	void cleanUpBuffer();

	unsigned int triCount;
	unsigned int vao, vbo, ibo;

};

