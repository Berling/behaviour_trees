#ifndef __CORE_ENGINE_HPP__
#define __CORE_ENGINE_HPP__

#include <memory>
#include <string>

#include <asset/asset_manager.hpp>
#include <ecs/component.hpp>
#include <ecs/entity.hpp>
#include <ecs/entity_manager.hpp>

namespace graphics {
	class graphics_system;
}

namespace rendering {
	class rendering_system;
}

namespace core {
	class engine {
	private:
		bool quit_;
		asset::asset_manager asset_manager_;
		std::unique_ptr<graphics::graphics_system> graphics_system_;
		std::unique_ptr<rendering::rendering_system> rendering_system_;
		ecs::entity_manager entity_manager_;

	public:
		engine() noexcept;
		~engine();

		engine(const engine& rhs) = delete;
		engine& operator=(const engine& rhs) = delete;

		engine(engine&& rhs) = delete;
		engine& operator=(engine&& rhs) = delete;

		void update(float delta_time);
		void run();
		void quit() noexcept;

		auto& asset_manager() {
			return asset_manager_;
		}

		auto& entity_manager() {
			return entity_manager_;
		}

		auto& graphics_system() {
			return *graphics_system_;
		}

		auto& rendering_system() {
			return *rendering_system_;
		}
	};
}

#endif
