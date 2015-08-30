#ifndef __GAMEPLAY_INVERT_NODE_HPP__
#define __GAMEPLAY_INVERT_NODE_HPP__

#include <gameplay/decorator_node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class invert_node : public decorator_node {
    public:
        invert_node(core::engine& engine, behaviour_tree_component& owner, node* parent);
        ~invert_node() = default;

        node_state update(float delta_time);    
    };
}

#endif
