#ifndef __GAMEPLAY_MOVEMENT_COMPONENT_HPP__
#define __GAMEPLAY_MOVEMENT_COMPONENT_HPP__

#include <glm/glm.hpp>

#include <ecs/component.hpp>
#include <utils/id_generator.hpp>

namespace core {
    class engine;
}

namespace ecs {
    class entity;
}

namespace gameplay {
    class gameplay_system;
}

namespace gameplay {
    class movement_component : public ecs::component {
    private:
        glm::vec2 velocity_;
        glm::vec2 acceleration_;
        float angular_velocity_;
        float angular_acceleration_;
        float max_velocity_;
        float max_acceleration_;
        float max_angular_velocity_;
        float max_angular_acceleration_;

    public:
        movement_component(core::engine& engine_, ecs::entity& owner) noexcept;
        ~movement_component();

        void update(float delta_time) noexcept;

        auto& velocity() const noexcept {
            return velocity_;
        }

        void velocity(const glm::vec2& velocity) noexcept {
            if (velocity.length() > max_velocity_) {
                velocity_ = glm::normalize(velocity) * max_velocity_;
            } else {
                velocity_ = velocity;
            }
        }

        auto& acceleration() const noexcept {
            return acceleration_;
        }

        void acceleration(const glm::vec2& acceleration) noexcept {
            if (acceleration.length() > max_acceleration_) {
                acceleration_ = glm::normalize(acceleration) * max_acceleration_;
            } else {
                acceleration_ = acceleration;
            }
        }

        auto angular_velocity() const noexcept {
            return angular_velocity_;
        }

        void angular_velocity(float angular_velocity) noexcept {
            angular_velocity_ = glm::clamp(angular_velocity, -max_angular_velocity_, max_angular_velocity_);
        }

        auto angular_acceleration() const noexcept {
            return angular_acceleration_;
        }

        void angular_acceleration(float angular_acceleration) {
            angular_acceleration_ = glm::clamp(angular_acceleration, -max_angular_acceleration_, max_angular_acceleration_);
        }

        auto max_velocity() const noexcept {
            return max_velocity_;
        }

        void max_velocity(float max_velocity) noexcept {
            max_velocity_ = max_velocity;
        }

        auto max_acceleration() const noexcept {
            return max_acceleration_;
        }

        void max_acceleration(float max_acceleration) noexcept {
            max_acceleration_ = max_acceleration;
        }

        auto max_angular_velocity() const noexcept {
            return max_angular_velocity_;
        }

        void max_angular_velocity(float max_angular_velocity) noexcept {
            max_angular_velocity_ = max_angular_velocity;
        }

        auto max_angular_acceleration() const noexcept {
            return max_angular_acceleration_;
        }

        void max_angular_acceleration(float max_angular_acceleration) noexcept {
            max_angular_acceleration_ = max_angular_acceleration;
        }

        static auto type_id() noexcept {
            return utils::type_id<movement_component>();
        }
    };
}

#endif
