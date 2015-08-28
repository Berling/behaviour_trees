#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/gameplay_system.hpp>
#include <gameplay/movement_component.hpp>

namespace gameplay {
    gameplay_system::gameplay_system(core::engine& engine) noexcept
    : engine_{engine} {}

    void gameplay_system::update(float delta_time) {
        for (auto& bt : behaviour_tree_components_) {
            bt->update(delta_time);
        }

        for (auto& mc : movement_components_) {
            mc->update(delta_time);
        }
    }

    void gameplay_system::register_component(behaviour_tree_component* component) {
        behaviour_tree_components_.emplace_back(component);
    }

    void gameplay_system::unregister_component(behaviour_tree_component* component) {
        auto it = std::find(behaviour_tree_components_.begin(), behaviour_tree_components_.end(), component);
        if (it != behaviour_tree_components_.end()) {
            std::iter_swap(it, behaviour_tree_components_.end() - 1);
            behaviour_tree_components_.pop_back();
        }
    }

    void gameplay_system::register_component(movement_component* component) {
        movement_components_.emplace_back(component);
    }

    void gameplay_system::unregister_component(movement_component* component) {
        auto it = std::find(movement_components_.begin(), movement_components_.end(), component);
        if (it != movement_components_.end()) {
            std::iter_swap(it, movement_components_.end() - 1);
            movement_components_.pop_back();
        }
    }
}
