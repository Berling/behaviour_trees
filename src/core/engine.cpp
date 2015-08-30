#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <utils/logger.hpp>

#include <core/engine.hpp>
#include <gameplay/alignment_component.hpp>
#include <gameplay/behaviour_tree_component.hpp>
#include <gameplay/gameplay_system.hpp>
#include <gameplay/flee_node.hpp>
#include <gameplay/movement_component.hpp>
#include <gameplay/move_random_node.hpp>
#include <gameplay/move_to_node.hpp>
#include <gameplay/selection_node.hpp>
#include <gameplay/sequence_node.hpp>
#include <gameplay/stop_movement_node.hpp>
#include <gameplay/success_node.hpp>
#include <gameplay/until_fail_node.hpp>
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

		auto& station = entity_manager_.emplace_back(glm::vec2{400.f, 300.f}, 0.f, glm::vec2{1.f});
		station.emplace_back<rendering::sprite_component>("textures/space_station.dds");
		auto& station_mc = station.emplace_back<gameplay::movement_component>();
		station_mc.angular_velocity(glm::radians(30.f));

		auto& s = entity_manager_.emplace_back(glm::vec2{200.f, 100.f}, 0.f, glm::vec2{1.f});
		s.emplace_back<rendering::sprite_component>("textures/enterprise.dds");
		s.emplace_back<gameplay::alignment_component>(gameplay::alignment::good);
		auto& mc = s.emplace_back<gameplay::movement_component>();
		auto& bt = s.emplace_back<gameplay::behaviour_tree_component>();
		auto& uf = bt.root<gameplay::until_fail_node>();
		auto& sn = uf.child<gameplay::sequence_node>();
		sn.emplace_back<gameplay::move_random_node>(station.id(), 200.f);

		auto& klingon = entity_manager_.emplace_back(glm::vec2{700.f, 500.f}, 0.f, glm::vec2{1.f});
		klingon.emplace_back<rendering::sprite_component>("textures/klingon.dds");
		klingon.emplace_back<gameplay::alignment_component>(gameplay::alignment::evil);
		klingon.emplace_back<gameplay::movement_component>();
		auto& kbt = klingon.emplace_back<gameplay::behaviour_tree_component>();
		auto& kuf = kbt.root<gameplay::until_fail_node>();
		auto& ksn = kuf.child<gameplay::sequence_node>();
		ksn.emplace_back<gameplay::move_random_node>(station.id(), 800.f);
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
