#ifndef __RENDERING_VERTEX_HPP__
#define __RENDERING_VERTEX_HPP__

#include <glm/glm.hpp>

namespace rendering {
    struct vertex {
        glm::vec2 position;
        glm::vec2 texcoord;
    };
}

#endif
