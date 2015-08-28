#ifndef __GAMEPLAY_GAMEPLAY_SYSTEM_HPP__
#define __GAMEPLAY_GAMEPLAY_SYSTEM_HPP__

#include <algorithm>
#include <vector>

namespace core {
    class game;
}

namespace gameplay {
    class movement_component;
}

namespace gameplay {
    class gameplay_system {
    private:
        core::engine& engine_;
        std::vector<movement_component*> movement_components_;

        friend class movement_component;

    public:
        gameplay_system(core::engine& engine) noexcept;
        ~gameplay_system() = default;

        gameplay_system(const gameplay_system& rhs) = delete;
        gameplay_system& operator=(const gameplay_system& rhs) = delete;

        gameplay_system(gameplay_system&& rhs) = delete;
        gameplay_system& operator=(gameplay_system&& rhs) = delete;

        void update(float delta_time);

    private:
        void register_component(movement_component* component);
        void unregister_component(movement_component* component);
    };
}

#endif
