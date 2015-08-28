#ifndef __ZOMBYE_ENTITY_HPP__
#define __ZOMBYE_ENTITY_HPP__

#include <memory>
#include <stdexcept>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <utils/logger.hpp>

namespace core {
    class engine;
}

namespace ecs {
    class entity {
    protected:
        core::engine& engine_;
        unsigned long long id_;
        std::unordered_map<unsigned long long, std::unique_ptr<ecs::component>> components_;
        glm::vec2 position_;
        float rotation_;
        glm::vec2 scale_;
        unsigned int layer_;

    public:
        entity(core::engine& engine, glm::vec2 position, float rotation, glm::vec2 scalation, unsigned int layer = 0) noexcept;
        ~entity() noexcept = default;

        entity(const entity& other) = delete;

        entity(entity&& other) = delete;

        template <typename component_type, typename... arguments>
        component_type& emplace_back(arguments... args) {
            auto it = components_.find(component_type::type_id());
            if (it == components_.end()) {
                components_.emplace(std::make_pair(component_type::type_id(), std::make_unique<component_type>(engine_, *this, std::forward<arguments>(args)...)));
            } else {
                utils::log(utils::log_level::LOG_WARNING) << "entity already has component with type id " << component_type::type_id() << std::endl;
            }
            return *static_cast<component_type*>(components_[component_type::type_id()].get());
        }

        template <typename component_type>
        component_type* component() noexcept {
            auto it = components_.find(component_type::type_id());
            if (it != components_.end()) {
                return static_cast<component_type*>(it->second.get());
            }
            return nullptr;
        }

        auto id() const noexcept {
            return id_;
        }

        auto& position() const noexcept {
            return position_;
        }

        void position(const glm::vec2& position) noexcept {
            position_ = position;
        }

        auto rotation() const noexcept {
            return rotation_;
        }

        void rotation(float rotation) noexcept {
            rotation_ = rotation;
        }

        auto& scale() const noexcept {
            return scale_;
        }

        void scale(const glm::vec2& scale) noexcept {
            scale_ = scale;
        }

        auto layer() const noexcept {
            return layer_;
        }

        void layer(unsigned int layer) noexcept {
            layer_ = layer;
        }

        glm::mat4 transform() const;
    };
}

#endif
