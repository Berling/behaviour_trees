#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/invert_node.hpp>

namespace gameplay {
    invert_node::invert_node(core::engine& engine, behaviour_tree_component& owner, node* parent)
    : decorator_node{engine, owner, parent} {}

    node_state invert_node::update(float delta_time) {
        auto result = child_->update(delta_time);
        if (result == node_state::success) {
            return node_state::failure;
        } else if (result == node_state::failure) {
            return node_state::success;
        } else {
            return result;
        }
    }
}
