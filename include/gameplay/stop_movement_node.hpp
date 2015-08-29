#ifndef __GAMEPLAY_STOP_MOVEMENT_NODE_HPP__
#define __GAMEPLAY_STOP_MOVEMENT_NODE_HPP__

#include <gameplay/node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class stop_movement_node : public node {
    public:
        stop_movement_node(core::engine& engine, behaviour_tree_component& owner, node* parent) noexcept;
        ~stop_movement_node() = default;

        node_state update(float delta_time);
    };
}

#endif
