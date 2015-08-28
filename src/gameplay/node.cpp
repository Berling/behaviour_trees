#include <gameplay/node.hpp>

namespace gameplay {
    node::node(core::engine& engine, behaviour_tree_component& owner, node* parent) noexcept
    : engine_{engine}, owner_{owner}, parent_{parent} {}
}
