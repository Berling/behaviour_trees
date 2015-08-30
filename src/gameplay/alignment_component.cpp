#include <core/engine.hpp>
#include <ecs/entity.hpp>
#include <gameplay/alignment_component.hpp>

namespace gameplay {
    alignment_component::alignment_component(core::engine& engine, ecs::entity& owner, gameplay::alignment alignment)
    : component{engine, owner}, alignment_{alignment} {}
}
