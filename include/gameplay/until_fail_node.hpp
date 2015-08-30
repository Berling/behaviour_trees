#ifndef __GAMEPLAY_UNTIl_FAIL_NODE_HPP__
#define __GAMEPLAY_UNTIl_FAIL_NODE_HPP__

#include <memory>

#include <gameplay/decorator_node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class until_fail_node : public decorator_node {
    public:
        until_fail_node(core::engine& engine, behaviour_tree_component& owner, node* parent);
        ~until_fail_node() = default;

        node_state update(float delta_time);
    };
}

#endif
