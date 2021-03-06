#include <glcw/vertex_array.hpp>

namespace glcw {
	vertex_array::vertex_array() noexcept {
		glGenVertexArrays(1, &id_);
		bind();
	}

	vertex_array::~vertex_array() {
		glDeleteVertexArrays(1, &id_);
	}

	vertex_array::vertex_array(vertex_array&& rhs) noexcept
	: id_{rhs.id_} {
		rhs.id_ = 0;
	}

	vertex_array& vertex_array::operator=(vertex_array&& rhs) noexcept {
		id_ = rhs.id_;
		rhs.id_ = 0;
		return *this;
	}

	void vertex_array::bind_vertex_attribute(const vertex_buffer& buffer, uint32_t index, int32_t size, GLenum type,
	bool normalized, size_t stride, intptr_t offset) noexcept {
		buffer.bind();
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<GLvoid*>(offset));
	}

	void vertex_array::bind_vertex_attributei(const vertex_buffer& buffer, uint32_t index, int32_t size, GLenum type,
	size_t stride, intptr_t offset) noexcept {
		buffer.bind();
		glEnableVertexAttribArray(index);
		glVertexAttribIPointer(index, size, type, stride, reinterpret_cast<GLvoid*>(offset));
	}

}