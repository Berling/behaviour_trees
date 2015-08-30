#ifndef __GAMEPLAY_ENEMY_SIGHTED_NODE_HPP__
#define __GAMEPLAY_ENEMY_SIGHTED_NODE_HPP__

#include <gameplay/node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class enemy_sighted_node : public node {
    private:
        float radius_;

    public:
        enemy_sighted_node(core::engine& engine, behaviour_tree_component& owner, node* parent, float radius);
        ~enemy_sighted_node() = default;

        node_state update(float delta_time);
    };
}

#endif
