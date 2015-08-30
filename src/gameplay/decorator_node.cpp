#include <gameplay/decorator_node.hpp>

namespace gameplay {
    decorator_node::decorator_node(core::engine& engine, behaviour_tree_component& owner, node* parent)
    : node{engine, owner, parent}, child_{nullptr} {}
}
