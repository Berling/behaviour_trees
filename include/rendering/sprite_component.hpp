#ifndef __RENDERING_SPRITE_COMPONENT_HPP__
#define __RENDERING_SPRITE_COMPONENT_HPP__

#include <string>

#include <ecs/component.hpp>
#include <graphics/texture_manager.hpp>
#include <utils/id_generator.hpp>

namespace ecs {
    class entity;
}

namespace core {
    class engine;
}

namespace rendering {
    class sprite_component : public ecs::component {
    private:
        graphics::texture_ptr texture_;

    public:
        sprite_component(core::engine& engine, ecs::entity& owner, const std::string& file_name);
        ~sprite_component();

        void bind(uint32_t unit) {
            texture_->bind(unit);
        }

        auto& texture() {
            return *texture_;
        }

        static auto type_id() noexcept {
            return utils::type_id<sprite_component>();
        }

    };
}

#endif
