#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/success_node.hpp>

namespace gameplay {
    success_node::success_node(core::engine& engine, behaviour_tree_component& owner, node* parent) noexcept
    : node{engine, owner, parent} {}

    node_state success_node::update(float delta_time) {
        return node_state::success;
    }
}
