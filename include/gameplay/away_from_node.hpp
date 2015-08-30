#ifndef __GAMEPLAY_AWAY_FROM_NODE_HPP__
#define __GAMEPLAY_AWAY_FROM_NODE_HPP__

#include <gameplay/node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class away_from_node : public node {
    private:
        unsigned long long target_;
        float distance_;

    public:
        away_from_node(core::engine& engine, behaviour_tree_component& owner, node* parent, unsigned long long target, float distance);
        ~away_from_node() = default;

        node_state update(float delta_time);
    };
}

#endif
