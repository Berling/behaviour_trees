#ifndef __GAMEPLAY_ALIGNMENT_COMPONENT_HPP__
#define __GAMEPLAY_ALIGNMENT_COMPONENT_HPP__

#include <ecs/component.hpp>
#include <utils/id_generator.hpp>

namespace core {
    class engine;
}

namespace ecs {
    class entity;
}

namespace gameplay {
    enum class alignment {
        good,
        evil
    };
}

namespace gameplay {
    class alignment_component : public ecs::component {
    private:
        gameplay::alignment alignment_;

    public:
        alignment_component(core::engine& engine, ecs::entity& owner, gameplay::alignment alignment);
        ~alignment_component() = default;

        auto alignment() const noexcept {
            return alignment_;
        }

        static auto type_id() noexcept {
            return utils::type_id<alignment_component>();
        }
    };
}

#endif
