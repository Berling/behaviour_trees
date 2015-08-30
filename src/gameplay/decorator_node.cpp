#include <gameplay/decorator_node.hpp>

namespace gameplay {
    decorator_node::decorator_node(core::engine& engine, behaviour_tree_component& owner, node* parent, std::unique_ptr<node>&& child)
    : node{engine, owner, parent}, child_{std::move(child)} {}
}
