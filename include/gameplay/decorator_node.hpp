#ifndef __GAMEPLAY_DECORATOR_NODE_HPP__
#define __GAMEPLAY_DECORATOR_NODE_HPP__

#include <memory>

#include <gameplay/node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class decorator_node : public node {
    private:
        std::unique_ptr<node> child_;

    public:
        decorator_node(core::engine& engine, behaviour_tree_component& owner, node* parent, std::unique_ptr<node>&& child);
        ~decorator_node() = default;

        virtual node_state update(float delta_time) = 0;
    };
}

#endif