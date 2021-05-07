#include "VertexBuffer.h"
#include "glad/glad.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID); //Generate one buffer and pointer to a unsigned int--> Generating a buffer and giving us an ID to refer later.
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); //Selecting(glbind**) the above buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //Put the data into the buffer
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); //Selecting(glbind**)
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
