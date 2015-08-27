#include <glm/gtc/matrix_transform.hpp>

#include <core/engine.hpp>
#include <ecs/component.hpp>
#include <ecs/entity.hpp>
#include <utils/id_generator.hpp>

namespace ecs {
    entity::entity(core::engine& engine, glm::vec2 position, float rotation, glm::vec2 scale, unsigned int layer) noexcept
    : engine_{engine}, id_{utils::id_generator<entity>()}, position_{position}, rotation_{rotation}, scale_{scale}, layer_{layer} { }

    glm::mat4 entity::transform() const {
        auto norm = glm::angleAxis(glm::radians(rotation_), glm::vec3{0.f, 0.f, 1.f});
        auto transform = glm::toMat4(norm);
        auto scale = glm::scale(glm::mat4{}, glm::vec3{scale_, 1.f});
        transform =  transform * scale;
        transform[3].x = position_.x;
        transform[3].y = position_.y;
        transform[3].z = static_cast<float>(layer_);
        return transform;
    }
}
