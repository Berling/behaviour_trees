#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/movement_component.hpp>
#include <gameplay/stop_movement_node.hpp>

namespace gameplay {
    stop_movement_node::stop_movement_node(core::engine& engine, behaviour_tree_component& owner, node* parent) noexcept
    : node{engine, owner, parent} {}

    node_state stop_movement_node::update(float delta_time) {
        auto& owner = owner_.owner();
        auto mc = owner.component<movement_component>();
        if (!mc) {
            return node_state::failure;
        }

        mc->velocity(glm::vec2{0.f});
        mc->acceleration(glm::vec2{0.f});
        mc->angular_velocity(0.f);
        mc->angular_acceleration(0.f);

        return node_state::success;
    }
}
