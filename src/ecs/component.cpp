#include <stdexcept>

#include <core/engine.hpp>
#include <ecs/component.hpp>
#include <ecs/entity.hpp>

namespace ecs {
    component::component(core::engine& engine, entity& owner) noexcept
    : engine_(engine), owner_(owner) { }

    component::~component() noexcept { }
}
