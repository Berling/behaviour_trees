#ifndef __GAMEPLAY_TARGET_COMPONENT_HPP__
#define __GAMEPLAY_TARGET_COMPONENT_HPP__

#include <ecs/component.hpp>
#include <utils/id_generator.hpp>

namespace core {
    class engine;
}

namespace ecs {
    class entity;
}

namespace gameplay {
    class target_component : public ecs::component {
    private:
        unsigned long long target_;

    public:
        target_component(core::engine& engine, ecs::entity& owner);
        ~target_component() = default;

        auto target() const noexcept {
            return target_;
        }

        void target(unsigned long long target) noexcept {
            target_ = target;
        }

        static auto type_id() noexcept {
            return utils::type_id<target_component>();
        }
    };
}

#endif
