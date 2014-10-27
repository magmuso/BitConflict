#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace BitEngine{
	class Input{
	public:
		Input();
		~Input();
		
		void update();

		const std::string & get_key_name(sf::Keyboard::Key key) const;
		bool is_key_pressed(sf::Keyboard::Key key) const;
		bool is_key_typed(sf::Keyboard::Key key) const;

		bool is_mouse_button_pressed(sf::Mouse::Button button) const;
		sf::Vector2i get_local_mouse_position() const;
		sf::Vector2i get_global_mouse_position() const;
		int get_mouse_wheel_change() const;
	private:
		sf::Event input_event;
		bool * typed_keys;
		std::string * key_names;
		void register_key_names();
	};
};
