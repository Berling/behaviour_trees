#include <glm/glm.hpp>

#include <core/engine.hpp>
#include <ecs/entity.hpp>
#include <gameplay/gameplay_system.hpp>
#include <gameplay/movement_component.hpp>
#include <graphics/graphics_system.hpp>

namespace gameplay {
    movement_component::movement_component(core::engine& engine, ecs::entity& owner) noexcept
    : component{engine, owner}, velocity_{0.f}, acceleration_{0.f}, angular_velocity_{0.f}, angular_acceleration_{0.f},
     max_velocity_{100.f}, max_acceleration_{100.f}, max_angular_velocity_{glm::radians(30.f)},
     max_angular_acceleration_{glm::radians(30.f)} {
        engine_.gameplay_system().register_component(this);
    }

    movement_component::~movement_component() {
        engine_.gameplay_system().unregister_component(this);
    }

    void movement_component::update(float delta_time) noexcept {
        velocity_ += delta_time * acceleration_;
        if (velocity_.length() > max_velocity_) {
            velocity_ = glm::normalize(velocity_);
            velocity_ *= max_velocity_;
        }

        auto position = owner_.position();
        position += delta_time * velocity_;
        if (position.x > engine_.graphics_system().width()) {
            position.x -= engine_.graphics_system().width();
        } else if (position.x < 0.f) {
            position.x += engine_.graphics_system().width();
        }
        if (position.y > engine_.graphics_system().height()) {
            position.y -= engine_.graphics_system().height();
        } else if (position.y < 0.f) {
            position.y += engine_.graphics_system().height();
        }
        owner_.position(position);

        angular_velocity_ += delta_time * angular_acceleration_;
        angular_velocity_ = glm::clamp(angular_velocity_, -max_angular_velocity_, max_angular_velocity_);

        auto rotation = owner_.rotation();
        rotation += delta_time * angular_velocity_;
        if (rotation > 2.f * glm::pi<float>()) {
            rotation -= 2.f * glm::pi<float>();
        } else if (rotation < -2.f * glm::pi<float>()) {
            rotation += 2.f * glm::pi<float>();
        }
        owner_.rotation(rotation);
    }
}