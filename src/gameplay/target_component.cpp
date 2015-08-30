#include <core/engine.hpp>
#include <ecs/entity.hpp>
#include <gameplay/target_component.hpp>

namespace gameplay {
    target_component::target_component(core::engine& engine, ecs::entity& owner)
    : component{engine, owner}, target_{0} {}
}
