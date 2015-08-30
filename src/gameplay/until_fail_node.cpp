#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/until_fail_node.hpp>

namespace gameplay {
    until_fail_node::until_fail_node(core::engine& engine, behaviour_tree_component& owner, node* parent)
    : decorator_node{engine, owner, parent} {}

    node_state until_fail_node::update(float delta_time) {
        auto result = child_->update(delta_time);
        if (result == node_state::failure) {
            return node_state::failure;
        }
        return node_state::pending;
    }
}
