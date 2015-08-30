#ifndef __GAMEPLAY_PARALLEL_NODE_HPP__
#define __GAMEPLAY_PARALLEL_NODE_HPP__

#include <memory>
#include <vector>

#include <gameplay/node.hpp>

namespace core {
    class engine;
}

namespace gameplay {
    class behaviour_tree_component;
    enum class node_state;
}

namespace gameplay {
    class parallel_node : public node {
    private:
        std::vector<std::unique_ptr<node>> nodes_;

    public:
        parallel_node(core::engine& engine, behaviour_tree_component& owner, node* parent);
        ~parallel_node() = default;

        node_state update(float delta_time);

        template <typename t, typename... arguments>
        auto& emplace_back(arguments&&... args) {
            nodes_.emplace_back(std::make_unique<t>(engine_, owner_, this, std::forward<arguments>(args)...));
            return *static_cast<t*>(nodes_.back().get());
        }
    };
}

#endif