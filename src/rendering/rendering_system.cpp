#include <algorithm>
#include <stdexcept>

#include <glm/gtc/matrix_transform.hpp>

#include <core/engine.hpp>
#include <ecs/entity.hpp>
#include <graphics/graphics_system.hpp>
#include <graphics/shader_manager.hpp>
#include <rendering/rectangle.hpp>
#include <rendering/rendering_system.hpp>
#include <rendering/sprite_component.hpp>
#include <rendering/vertex.hpp>

namespace rendering {
    rendering_system::rendering_system(core::engine& engine) noexcept
    : engine_{engine} {
        sprite_vertex_layout_.emplace_back("_position", 2, GL_FLOAT, false, sizeof(vertex), offsetof(vertex, position));
        sprite_vertex_layout_.emplace_back("_texcoord", 2, GL_FLOAT, false, sizeof(vertex), offsetof(vertex, texcoord));

        auto& graphics_system = engine_.graphics_system();

        auto vertex_shader = graphics_system.shader_manager().load("shaders/sprite.vs", GL_VERTEX_SHADER);
        if (!vertex_shader) {
            throw std::runtime_error{"could not load shader from file shaders/sprite.vs"};
        }
        sprite_program_.attach_shader(vertex_shader);

        auto fragment_shader = graphics_system.shader_manager().load("shaders/sprite.fs", GL_FRAGMENT_SHADER);
        if (!fragment_shader) {
            throw std::runtime_error{"could not load shader from file shaders/sprite.fs"};
        }
        sprite_program_.attach_shader(fragment_shader);

        sprite_vertex_layout_.setup_program(sprite_program_, "frag_color");
        sprite_program_.link();

        auto width = static_cast<float>(graphics_system.width());
        auto height = static_cast<float>(graphics_system.height());
        projection_ = glm::ortho(0.f, width, height, 0.f);

        rectangle_ = std::make_unique<rectangle>(*this);
    }

    void rendering_system::update(float delta_time) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        sprite_program_.use();
        sprite_program_.uniform("projection", false, projection_);
        sprite_program_.uniform("view", false, view_);
        for (auto& sprite : sprite_components_) {
            sprite_program_.uniform("model", false, sprite->owner().transform());
            sprite_program_.uniform("albedo", 0);
            sprite->bind(0);
            rectangle_->draw();
        }

        glDisable(GL_BLEND);
    }

    void rendering_system::register_component(sprite_component* component) {
        sprite_components_.emplace_back(component);
    }

    void rendering_system::unregister_component(sprite_component* component) {
        auto it = std::find(sprite_components_.begin(), sprite_components_.end(), component);
        if (it != sprite_components_.end()) {
            std::iter_swap(it, sprite_components_.end() - 1);
            sprite_components_.pop_back();
        }
    }
}
