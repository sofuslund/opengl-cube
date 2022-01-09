#pragma once
#include <glad/glad.h>

class VertexBuffer
{
private:
	GLuint m_RendererID;
public:
	VertexBuffer(const void* data, GLuint size, GLenum usage);

	void Bind() const;
	void UnBind() const;

	void CleanUp();
	~VertexBuffer();
};

