#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace BitEngine {
	class Input {
	public:
		Input();
		~Input();
		
		void update();

		const std::string getKeyName(sf::Keyboard::Key key) const;
		bool isKeyPressed(sf::Keyboard::Key key) const;
		bool isKeyTyped(sf::Keyboard::Key key) const;

		bool isMouseButtonPressed(sf::Mouse::Button button) const;
		sf::Vector2i getLocalMousePosition() const;
		sf::Vector2i getGlobalMousePosition() const;
		int getMouseWheelChange() const;
	private:
		sf::Event _input_event;
		bool * _typed_keys;
		std::string * _key_names;
		void register_key_names();
	};
};
