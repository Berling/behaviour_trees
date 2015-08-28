#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <utils/logger.hpp>

#include <core/engine.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/gameplay_system.hpp>
#include <gameplay/movement_component.hpp>
#include <gameplay/success_node.hpp>
#include <graphics/graphics_system.hpp>
#include <rendering/rectangle.hpp>
#include <rendering/rendering_system.hpp>
#include <rendering/sprite_component.hpp>

using namespace std::literals;

namespace core {
	engine::engine() noexcept
	: quit_{false}, entity_manager_{*this} {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			auto sdl_error = std::string{SDL_GetError()};
			SDL_ClearError();
			throw std::runtime_error{"could not initialize SDL" + sdl_error};
		}

		graphics_system_ = std::make_unique<graphics::graphics_system>(*this);
		rendering_system_ = std::make_unique<rendering::rendering_system>(*this);
		gameplay_system_ = std::make_unique<gameplay::gameplay_system>(*this);

		auto& s = entity_manager_.emplace_back(glm::vec2{400.f, 300.f}, 0.f, glm::vec2{1.f});
		s.emplace_back<rendering::sprite_component>("textures/enterprise.dds");
		auto& mc = s.emplace_back<gameplay::movement_component>();
		mc.angular_velocity(glm::radians(30.f));
		mc.acceleration(glm::vec2{3.f, -2.f});
		auto& bt = s.emplace_back<gameplay::behaviour_tree_component>();
		bt.root<gameplay::success_node>();
	}

	engine::~engine() {
		SDL_Quit();
	}

	void engine::update(float delta_time) {
		gameplay_system_->update(delta_time);

		graphics_system_->begin();
		rendering_system_->update(delta_time);
		graphics_system_->end(delta_time);
	}

	void engine::run() {
		auto event = SDL_Event{};
		auto last_time = 0.f;
		auto current_time = SDL_GetTicks() / 1000.f;
		auto delta_time = 0.f;

		while (!quit_) {
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					quit_ = true;
				} else if (event.type == SDL_KEYDOWN) {

				}
			}
			last_time = current_time;
			current_time = SDL_GetTicks() / 1000.f;
			delta_time = current_time - last_time;

			update(delta_time);
			entity_manager_.clear();
		}
	}

	void engine::quit() noexcept {
		quit_ = true;
	}
}
