#ifndef __GAMEPLAY_BEHAVIOUR_TREE_COMPONENT_HPP__
#define __GAMEPLAY_BEHAVIOUR_TREE_COMPONENT_HPP__

#include <memory>

#include <ecs/component.hpp>
#include <utils/id_generator.hpp>

namespace core {
    class engine;
}

namespace ecs {
    class entity;
}

namespace gameplay {
    class node;
}

namespace gameplay {
    enum class node_state {
        failure,
        success,
        pending
    };
}

namespace gameplay {
    class behaviour_tree_component : public ecs::component {
    private:
        std::unique_ptr<node> root_;
        node* current_node_;

    public:
        behaviour_tree_component(core::engine& engine, ecs::entity& owner) noexcept;
        ~behaviour_tree_component();

        void update(float delta_time);

        auto& root() noexcept {
            return *root_;
        }

        template <typename t, typename... arguments>
        void root(arguments&&... args) {
            root_ = std::make_unique<t>(engine_, *this, nullptr, std::forward<arguments>(args)...);
            current_node_ = root_.get();
        }

        auto current_node() noexcept {
            return current_node_;
        }

        void current_node(node* current_node) noexcept {
            current_node_ = current_node;
        }

        static auto type_id() noexcept {
            return utils::type_id<behaviour_tree_component>();
        }
    };
}

#endif
