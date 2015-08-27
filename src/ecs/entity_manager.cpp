#include <core/engine.hpp>
#include <ecs/component.hpp>
#include <ecs/entity.hpp>

namespace ecs {
    entity_manager::entity_manager(core::engine& engine) noexcept : engine_(engine) {}

    entity& entity_manager::emplace_back(const glm::vec2& position, float rotation,
    const glm::vec2& scalation, unsigned int layer) {
        auto entity = new ecs::entity{engine_, position, rotation, scalation, layer};
        entities_.insert(std::make_pair(entity->id(), std::unique_ptr<ecs::entity>(entity)));
        return *entity;
    }

    void entity_manager::erase(unsigned long long id) {
        auto it = entities_.find(id);
        if (it != entities_.end()) {
            deletion_.push(id);
        } else {
            utils::log(utils::log_level::LOG_WARNING) << "entity " << id << "doesn't exist" << std::endl;
        }
    }

    void entity_manager::clear() {
        while (!deletion_.empty()) {
            unsigned int kill = deletion_.front();
            auto it = entities_.find(kill);
            if (it != entities_.end()) {
                entities_.erase(it);
            } else {
                utils::log(utils::log_level::LOG_WARNING) << "entity " << kill << " was already destroyed" << std::endl;
            }
            deletion_.pop();
        }
    }

    entity* entity_manager::resolve(unsigned long long id) noexcept {
        auto it = entities_.find(id);
        if (it != entities_.end()) {
            return it->second.get();
        }
        return nullptr;
    }
}
