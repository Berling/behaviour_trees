#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/sequence_node.hpp>

namespace gameplay {
    sequence_node::sequence_node(core::engine& engine, behaviour_tree_component& owner, node* parent) noexcept
    : node{engine, owner, parent}, current_node_{0} {}

    node_state sequence_node::update(float delta_time) {
        if (nodes_.size() == 0) {
            return node_state::failure;
        }

        auto result = nodes_[current_node_]->update(delta_time);
        if (result == node_state::failure) {
            return node_state::failure;
        } else if (result == node_state::success) {
            if (current_node_ < nodes_.size() - 1) {
                ++current_node_;
            } else {
                return node_state::success;
            }
        }
        return node_state::pending;
    }
}
