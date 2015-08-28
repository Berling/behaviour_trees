#ifndef __RENDERING_RENDERING_SYSTEM_HPP__
#define __RENDERING_RENDERING_SYSTEM_HPP__

#include <memory>
#include <vector>

#include <glcw/program.hpp>
#include <glcw/vertex_layout.hpp>

#include <glm/glm.hpp>

namespace core {
    class engine;
}

namespace rendering {
    class rectangle;
    class sprite_component;
}

namespace rendering {
    class rendering_system {
    private:
        core::engine& engine_;
        glcw::vertex_layout sprite_vertex_layout_;
        glcw::program sprite_program_;
        glm::mat4 projection_;
        glm::mat4 view_;
        std::unique_ptr<rectangle> rectangle_;

        std::vector<sprite_component*> sprite_components_;

        friend class sprite_component;

    public:
        rendering_system(core::engine& engine) noexcept;
        ~rendering_system() = default;

        rendering_system(const rendering_system& rhs) = delete;
        rendering_system& operator=(const rendering_system& rhs) = delete;

        rendering_system(rendering_system&& rhs) = delete;
        rendering_system& operator=(rendering_system&& rhs) = delete;

        void update(float delta_time);

        auto& sprite_vertex_layout() noexcept {
            return sprite_vertex_layout_;
        }

    private:
        void register_component(sprite_component* component);
        void unregister_component(sprite_component* component);
    };
}

#endif
