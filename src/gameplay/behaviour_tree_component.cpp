#include <core/engine.hpp>
#include <ecs/entity.hpp>
#include <gameplay/node.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/gameplay_system.hpp>

namespace gameplay {
    behaviour_tree_component::behaviour_tree_component(core::engine& engine, ecs::entity& owner) noexcept
    : component{engine, owner}, root_{nullptr}, current_node_{nullptr} {
        engine_.gameplay_system().register_component(this);
    }

    behaviour_tree_component::~behaviour_tree_component() {
        engine_.gameplay_system().unregister_component(this);
    }

    void behaviour_tree_component::update(float delta_time) {
        if (current_node_) {
            auto state = current_node_->update(delta_time);
            if (current_node_ == root_.get() && state != node_state::pending) {
                current_node_ = nullptr;
            }
        }
    }
}
