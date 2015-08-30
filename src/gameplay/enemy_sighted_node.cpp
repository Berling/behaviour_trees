#include <core/engine.hpp>
#include <ecs/entity_manager.hpp>
#include <gameplay/alignment_component.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/enemy_sighted_node.hpp>

namespace gameplay {
    enemy_sighted_node::enemy_sighted_node(core::engine& engine, behaviour_tree_component& owner, node* parent, float radius)
    : node{engine, owner, parent}, radius_{radius} {}

    node_state enemy_sighted_node::update(float delta_time) {
        auto& owner = owner_.owner();
        auto owner_alignment = owner.component<alignment_component>();
        if (!owner_alignment) {
            return node_state::failure;
        }
        auto owner_position = owner.position();

        auto current = 1;
        auto enemy = engine_.entity_manager().resolve(current);
        while (enemy) {
            auto alignment = enemy->component<alignment_component>();
            if (alignment) {
                if (owner_alignment->alignment() != alignment->alignment()) {
                    auto enemy_position = enemy->position();
                    auto distance = enemy_position - owner_position;
                    if (glm::length(distance) <= radius_) {
                        return node_state::success;
                    }
                }
            }

            enemy = engine_.entity_manager().resolve(current++);
        }

        return node_state::failure;
    }
}
