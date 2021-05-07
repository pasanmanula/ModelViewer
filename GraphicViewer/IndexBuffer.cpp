#include "IndexBuffer.h"
#include "glad/glad.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID); //One buffer and pointer to a unsigned int--> Generating a buffer and giving us an ID to refer later.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); //Selecting(glbind**) the above buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //Put the data into the buffer
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); //Selecting(glbind**)
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
