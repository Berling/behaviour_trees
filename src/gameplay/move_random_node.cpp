#include <limits>
#include <random>

#include <glm/glm.hpp>

#include <core/engine.hpp>
#include <ecs/entity.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/movement_component.hpp>
#include <gameplay/move_random_node.hpp>

namespace gameplay {
    move_random_node::move_random_node(core::engine& engine, behaviour_tree_component& owner, node* parent, unsigned long long target, float distance) noexcept
    : node{engine, owner, parent}, target_{target}, distance_{distance} {}

    node_state move_random_node::update(float delta_time) {
        auto target = engine_.entity_manager().resolve(target_);
        if (!target) {
            return node_state::failure;
        }

        auto& owner = owner_.owner();
        auto mc = owner.component<movement_component>();
        if (!mc) {
            return node_state::failure;
        }

        static std::random_device rd;
        static std::mt19937 rng{rd()};
        static std::uniform_int_distribution<float> uni{0, 360};
        static auto target_set = false;
        static auto alpha = 0.f;
        if (!target_set) {
            alpha = glm::radians(uni(rng));
            target_set = true;
        }

        auto target_position = target->position();
        auto owner_position = owner.position();
        auto new_position = glm::vec2{glm::cos(alpha), glm::sin(alpha)} * distance_ + target_position;
        auto distance = new_position - owner_position;
        if (glm::length(distance) <= 100.f) {
            target_set = false;
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
