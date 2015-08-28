#ifndef __GAMEPLAY_NODE_HPP__
#define __GAMEPLAY_NODE_HPP__

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class node {
    private:
        core::engine& engine_;
        behaviour_tree_component& owner_;
        node* parent_;

    public:
        node(core::engine& engine, behaviour_tree_component& owner, node* parent) noexcept;
        virtual ~node() = default;

        node(const node& rhs) = delete;
        node& operator=(const node& rhs) = delete;

        node(node&& rhs) = delete;
        node& operator=(node&& rhs) = delete;

        virtual node_state update(float delta_time) = 0;

        node* parent() noexcept {
            return parent_;
        }
    };
}

#endif
