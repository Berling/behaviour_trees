#ifndef __GAMEPLAY_MOVE_TO_NODE_HPP__
#define __GAMEPLAY_MOVE_TO_NODE_HPP__

#include <gameplay/node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class move_to_node : public node {
    private:
        unsigned long long target_;
        float min_distance_;

    public:
        move_to_node(core::engine& engine, behaviour_tree_component& owner, node* parent, unsigned long long target, float min_distance) noexcept;
        ~move_to_node() = default;

        node_state update(float delta_time);

        auto target() const noexcept {
            return target_;
        }

        void target(unsigned long long target) noexcept {
            target_ = target;
        }
    };
}

#endif
