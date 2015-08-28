#ifndef __GAMEPLAY_SUCCESS_NODE_HPP__
#define __GAMEPLAY_SUCCESS_NODE_HPP__

#include <gameplay/node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class success_node : public node {
    public:
        success_node(core::engine& engine, behaviour_tree_component& owner, node* parent) noexcept;
        ~success_node() = default;

        node_state update(float delta_time) override;
    };
}

#endif
