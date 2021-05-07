#pragma once

#include "VertexBuffer.h"

class VertexArray {
private:
	unsigned int m_RendererID;
public:
	VertexArray(const unsigned int count);
	~VertexArray();

	void Bind() const;
	void Unbind() const;
};