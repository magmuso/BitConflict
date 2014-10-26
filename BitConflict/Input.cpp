#include "Input.h"
#include "BitConflict.h"
using namespace BitEngine;

Input::Input()
{
	typed_keys = new bool[sf::Keyboard::KeyCount];
	input_event = sf::Event();
}


Input::~Input()
{
	delete[] typed_keys;
}


void Input::update()
{
	memset(typed_keys, false, sf::Keyboard::KeyCount);
	sf::RenderWindow * window = g_game->u_graphics->u_window->xx_sfml_window();
	while (window->pollEvent(input_event))
	{
		if (input_event.type == sf::Event::Closed)
			window->close();
		if (input_event.type == sf::Event::KeyPressed) {
			if (input_event.key.code == sf::Keyboard::F4 && input_event.key.alt)
				window->close();
			typed_keys[input_event.key.code] = true;
		}
	}
}


bool Input::is_key_pressed(sf::Keyboard::Key key) const
{
	return sf::Keyboard::isKeyPressed(key);
}


bool Input::is_key_typed(sf::Keyboard::Key key) const
{
	return typed_keys[key];
}


bool Input::is_mouse_button_pressed(sf::Mouse::Button button) const
{
	return sf::Mouse::isButtonPressed(button);
}


sf::Vector2i Input::get_local_mouse_position() const
{
	auto window = g_game->u_graphics->u_window->xx_sfml_window();
	return sf::Mouse::getPosition(*window);
}


sf::Vector2i Input::get_global_mouse_position() const
{
	return sf::Mouse::getPosition();
}