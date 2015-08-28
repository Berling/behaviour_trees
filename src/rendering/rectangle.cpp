#include <rendering/rectangle.hpp>
#include <rendering/rendering_system.hpp>
#include <rendering/vertex.hpp>

namespace rendering {
    rectangle::rectangle(rendering_system& rendering_system) noexcept
    : vbo_{GL_STATIC_DRAW} {
        vertex vertices[6] = {
            {glm::vec2{-0.5f, 0.5f}, glm::vec2{0.f, 1.f}},
            {glm::vec2{-0.5f, -0.5f}, glm::vec2{0.f, 0.f}},
            {glm::vec2{0.5f, 0.5f}, glm::vec2{1.f, 1.f}},
            {glm::vec2{0.5f, 0.5f}, glm::vec2{1.f, 1.f}},
            {glm::vec2{-0.5f, -0.5f}, glm::vec2{0.f, 0.f}},
            {glm::vec2{0.5f, -0.5f}, glm::vec2{1.f, 0.f}},
        };
        vbo_.data(6 * sizeof(vertex), vertices);
        rendering_system.sprite_vertex_layout().setup_layout(vao_, &vbo_);
    }

    void rectangle::draw() {
        vao_.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
