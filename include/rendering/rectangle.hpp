#ifndef __RENDERING_RECTANGLE_HPP__
#define __RENDERING_RECTANGLE_HPP__

#include <glcw/buffer.hpp>
#include <glcw/vertex_array.hpp>

namespace rendering {
    class rendering_system;
}

namespace rendering {
    class rectangle {
    private:
        glcw::vertex_array vao_;
        glcw::vertex_buffer vbo_;

    public:
        rectangle(rendering_system& rendering_system) noexcept;
        ~rectangle() = default;

        rectangle(const rectangle& rhs) = delete;
        rectangle& operator=(const rectangle& rhs) = delete;

        rectangle(rectangle&& rhs) = delete;
        rectangle& operator=(rectangle&& rhs) = delete;

        void draw();

        auto& vao() {
            return vao_;
        }

        auto& vbo() {
            return vbo_;
        }
    };
}

#endif
