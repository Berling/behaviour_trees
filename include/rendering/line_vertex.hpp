#ifndef __RENDERING_LINE_VERTEX_HPP__
#define __RENDERING_LINE_VERTEX_HPP__

#include <glm/glm.hpp>

namespace rendering {
    struct line_vertex {
        glm::vec2 position;
        glm::vec3 color;
    };
}

#endif
