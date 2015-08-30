#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/selection_node.hpp>

namespace gameplay {
    selection_node::selection_node(core::engine& engine, behaviour_tree_component& owner, node* parent)
    : node{engine, owner, parent}, current_node_{0} {}

    node_state selection_node::update(float delta_time) {
        if (nodes_.size() == 0) {
            return node_state::failure;
        }

        auto result = nodes_[current_node_]->update(delta_time);
        if (result == node_state::success) {
            current_node_ = 0;
            return node_state::success;
        } else if (result == node_state::failure) {
            if (current_node_ < nodes_.size() - 1) {
                ++current_node_;
            } else {
                current_node_ = 0;
                return node_state::failure;
            }
        }
        return node_state::pending;
    }
}
