#include <glm/glm.hpp>

#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/flee_node.hpp>
#include <gameplay/movement_component.hpp>
#include <gameplay/target_component.hpp>

namespace gameplay {
    flee_node::flee_node(core::engine& engine, behaviour_tree_component& owner, node* parent, unsigned long long target, float distance) noexcept
    : node{engine, owner, parent}, target_{target}, distance_{distance} {}

    node_state flee_node::update(float delta_time) {
        auto& owner = owner_.owner();

        ecs::entity* target = nullptr;
        if (target_ == 0) {
            auto tc = owner.component<target_component>();
            if (!tc) {
                return node_state::failure;
            }
            target = engine_.entity_manager().resolve(tc->target());
            if (!target) {
                return node_state::failure;
            }
        } else {
            target = engine_.entity_manager().resolve(target_);
            if (!target) {
                return node_state::failure;
            }
        }

        auto mc = owner.component<movement_component>();
        if (!mc) {
            return node_state::failure;
        }

        auto target_position = target->position();
        auto owner_position = owner_.owner().position();
        auto distance = owner_position - target_position;
        if (glm::length(distance) > distance_) {
            return node_state::success;
        }
        auto direction = glm::normalize(distance);
        mc->acceleration(direction * mc->max_acceleration());

        auto velocity = mc->velocity();
        auto angle = glm::atan(velocity.y, velocity.x);
        owner.rotation(angle);

        return node_state::pending;
    }
}
