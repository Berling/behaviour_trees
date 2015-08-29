#include <limits>

#include <glm/glm.hpp>

#include <core/engine.hpp>
#include <ecs/entity.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/movement_component.hpp>
#include <gameplay/move_to_node.hpp>

namespace gameplay {
    move_to_node::move_to_node(core::engine& engine, behaviour_tree_component& owner, node* parent, unsigned long long target, float min_distance) noexcept
    : node{engine, owner, parent}, target_{target}, min_distance_{min_distance} {}

    node_state move_to_node::update(float delta_time) {
        auto target = engine_.entity_manager().resolve(target_);
        if (!target) {
            return node_state::failure;
        }

        auto& owner = owner_.owner();
        auto mc = owner.component<movement_component>();
        if (!mc) {
            return node_state::failure;
        }

        auto target_position = target->position();
        auto owner_position = owner_.owner().position();
        auto distance = target_position - owner_position;
        if (glm::length(distance) <= min_distance_) {
            mc->velocity(glm::vec2{0.f});
            mc->acceleration(glm::vec2{0.f});
            return node_state::success;
        }
        auto direction = glm::normalize(distance);
        mc->acceleration(direction * 20.f);

        auto velocity = mc->velocity();
        auto angle = glm::atan(velocity.y, velocity.x);
        owner.rotation(angle);
        mc->angular_velocity(0.f);
        mc->angular_acceleration(0.f);

        return node_state::pending;
    }
}
