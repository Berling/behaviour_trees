#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/parallel_node.hpp>

namespace gameplay {
    parallel_node::parallel_node(core::engine& engine, behaviour_tree_component& owner, node* parent)
    : node{engine, owner, parent} {}

    node_state parallel_node::update(float delta_time) {
        if (nodes_.size() == 0) {
            return node_state::failure;
        }

        auto status = 0ull;

        for (auto& node : nodes_) {
            auto result = node->update(delta_time);
            if (result == node_state::failure) {
                return node_state::failure;
            } else if (result == node_state::success) {
                ++status;
            }
        }

        if (status == nodes_.size()) {
            return node_state::success;
        }

        return node_state::pending;
    }
}
