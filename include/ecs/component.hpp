#ifndef __ECS_COMPONENT_HPP__
#define __ECS_COMPONENT_HPP__

namespace core {
    class engine;
}

namespace ecs {
    class entity;
}

namespace ecs {
    class component {
    protected:
        core::engine& engine_;
        entity& owner_;

    public:
        component(core::engine& engine_, entity& owner) noexcept;
        virtual ~component() noexcept = 0;

        component(const component& other) = delete;
        component& operator= (const component& other) = delete;

        component(component&& other) = delete;
        component& operator= (component&& other) = delete;

        auto& owner() const noexcept {
            return owner_;
        }

        virtual unsigned long long type_id() const noexcept = 0;
    };
}

#endif
