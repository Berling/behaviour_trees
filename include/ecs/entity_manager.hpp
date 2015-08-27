#ifndef __ECS_ENTITY_MANAGER_HPP__
#define __ECS_ENTITY_MANAGER_HPP__

#include <memory>
#include <queue>
#include <unordered_map>

#include <glm/glm.hpp>

namespace core {
    class engine;
}

namespace ecs {
    class entity;
}

namespace ecs {
    class entity_manager {
        core::engine& engine_;
        std::unordered_map<unsigned long long, std::unique_ptr<entity>> entities_;
        std::queue<unsigned long long> deletion_;

    public:
        entity_manager(core::engine& engine) noexcept;
        ~entity_manager() = default;

        entity_manager(const entity_manager& other) = delete;
        entity_manager& operator= (const entity_manager& other) = delete;

        entity_manager(entity_manager&& other) = delete;
        entity_manager& operator= (entity_manager&& other) = delete;

        entity& emplace_back(const glm::vec2& position, float rotation, const glm::vec2& scalation, unsigned int layer = 0);
        void erase(unsigned long long id);
        void clear();
        entity* resolve(unsigned long long id) noexcept;
    };
}

#endif
