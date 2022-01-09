#pragma once
#include <glad/glad.h>

class IndexBuffer
{
private:
	GLuint m_RendererID;
	GLuint m_Count;
public:
	IndexBuffer(const GLuint* data, GLuint count, GLenum usage);

	void Bind() const;
	void UnBind() const;

	inline GLuint GetCount() const { return m_Count; }

	void CleanUp();
	~IndexBuffer();
};