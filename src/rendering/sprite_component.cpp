#include <stdexcept>

#include <core/engine.hpp>
#include <ecs/entity.hpp>
#include <graphics/graphics_system.hpp>
#include <rendering/rendering_system.hpp>
#include <rendering/sprite_component.hpp>

namespace rendering {
    sprite_component::sprite_component(core::engine& engine, ecs::entity& owner, const std::string& file_name)
    : component{engine, owner} {
        engine_.rendering_system().register_component(this);

        texture_ = engine_.graphics_system().texture_manager().load(file_name);
        if (!texture_) {
            throw std::runtime_error{"could not load texture from file " + file_name};
        }

        owner.scale(
            glm::vec2{
                static_cast<float>(texture_->width()),
                static_cast<float>(texture_->height())
            }
        );
    }

    sprite_component::~sprite_component() {
        engine_.rendering_system().unregister_component(this);
    }
}
