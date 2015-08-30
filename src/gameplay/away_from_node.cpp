#include <glm/glm.hpp>

#include <core/engine.hpp>
#include <gameplay/away_from_node.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/target_component.hpp>

namespace gameplay {
    away_from_node::away_from_node(core::engine& engine, behaviour_tree_component& owner, node* parent, unsigned long long target, float distance)
    : node{engine, owner, parent}, target_{target}, distance_{distance} {}

    node_state away_from_node::update(float delta_time) {
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

        auto target_position = target->position();
        auto owner_position = owner.position();
        auto distance = owner_position - target_position;
        if (glm::length(distance) >= distance_) {
            return node_state::success;
        }
        return node_state::failure;
    }
}
