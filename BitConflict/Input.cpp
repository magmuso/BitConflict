#include "Input.h"
#include "BitConflict.h"
using namespace BitEngine;

Input::Input()
{
	typed_keys = new bool[sf::Keyboard::KeyCount];
	key_names = new std::string[sf::Keyboard::KeyCount];
	register_key_names();
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


const std::string & Input::get_key_name(sf::Keyboard::Key key) const
{
	if (key != -1 && key < sf::Keyboard::KeyCount)
	{
		return key_names[key];
	}
	else
	{
		return "Unknown Key";
	}
}


void Input::register_key_names()
{
	key_names[sf::Keyboard::Escape] = "Escape";
	key_names[sf::Keyboard::F1] = "F1";
	key_names[sf::Keyboard::F2] = "F2";
	key_names[sf::Keyboard::F3] = "F3";
	key_names[sf::Keyboard::F4] = "F4";
	key_names[sf::Keyboard::F5] = "F5";
	key_names[sf::Keyboard::F6] = "F6";
	key_names[sf::Keyboard::F7] = "F7";
	key_names[sf::Keyboard::F8] = "F8";
	key_names[sf::Keyboard::F9] = "F9";
	key_names[sf::Keyboard::F10] = "F10";
	key_names[sf::Keyboard::F11] = "F11";
	key_names[sf::Keyboard::F12] = "F12";
	key_names[sf::Keyboard::Insert] = "Insert";
	key_names[sf::Keyboard::Delete] = "Delete";
	key_names[sf::Keyboard::Home] = "Home";
	key_names[sf::Keyboard::End] = "End";
	key_names[sf::Keyboard::PageUp] = "PageUp";
	key_names[sf::Keyboard::PageDown] = "PageDown";
	key_names[sf::Keyboard::Tilde] = "Tilde";
	key_names[sf::Keyboard::Num1] = "Num1";
	key_names[sf::Keyboard::Num2] = "Num2";
	key_names[sf::Keyboard::Num3] = "Num3";
	key_names[sf::Keyboard::Num4] = "Num4";
	key_names[sf::Keyboard::Num5] = "Num5";
	key_names[sf::Keyboard::Num6] = "Num6";
	key_names[sf::Keyboard::Num7] = "Num7";
	key_names[sf::Keyboard::Num8] = "Num8";
	key_names[sf::Keyboard::Num9] = "Num9";
	key_names[sf::Keyboard::Num0] = "Num0";
	key_names[sf::Keyboard::Dash] = "Dash";
	key_names[sf::Keyboard::Equal] = "Equal";
	key_names[sf::Keyboard::BackSpace] = "BackSpace";
	key_names[sf::Keyboard::Tab] = "Tab";
	key_names[sf::Keyboard::Q] = "Q";
	key_names[sf::Keyboard::W] = "W";
	key_names[sf::Keyboard::E] = "E";
	key_names[sf::Keyboard::R] = "R";
	key_names[sf::Keyboard::T] = "T";
	key_names[sf::Keyboard::Y] = "Y";
	key_names[sf::Keyboard::U] = "U";
	key_names[sf::Keyboard::I] = "I";
	key_names[sf::Keyboard::O] = "O";
	key_names[sf::Keyboard::P] = "P";
	key_names[sf::Keyboard::LBracket] = "LBracket";
	key_names[sf::Keyboard::RBracket] = "RBracket";
	key_names[sf::Keyboard::BackSlash] = "BackSlash";
	key_names[sf::Keyboard::A] = "A";
	key_names[sf::Keyboard::S] = "S";
	key_names[sf::Keyboard::D] = "D";
	key_names[sf::Keyboard::F] = "F";
	key_names[sf::Keyboard::G] = "G";
	key_names[sf::Keyboard::H] = "H";
	key_names[sf::Keyboard::J] = "J";
	key_names[sf::Keyboard::K] = "K";
	key_names[sf::Keyboard::L] = "L";
	key_names[sf::Keyboard::SemiColon] = "SemiColon";
	key_names[sf::Keyboard::Quote] = "Quote";
	key_names[sf::Keyboard::Return] = "Enter";
	key_names[sf::Keyboard::LShift] = "LShift";
	key_names[sf::Keyboard::Z] = "Z";
	key_names[sf::Keyboard::X] = "X";
	key_names[sf::Keyboard::C] = "C";
	key_names[sf::Keyboard::V] = "V";
	key_names[sf::Keyboard::B] = "B";
	key_names[sf::Keyboard::N] = "N";
	key_names[sf::Keyboard::M] = "M";
	key_names[sf::Keyboard::Comma] = "Comma";
	key_names[sf::Keyboard::Period] = "Period";
	key_names[sf::Keyboard::Slash] = "Slash";
	key_names[sf::Keyboard::RShift] = "RShift";
	key_names[sf::Keyboard::LControl] = "LControl";
	key_names[sf::Keyboard::LAlt] = "LAlt";
	key_names[sf::Keyboard::Space] = "Space";
	key_names[sf::Keyboard::RControl] = "RControl";
	key_names[sf::Keyboard::RAlt] = "RAlt";
	key_names[sf::Keyboard::Left] = "Left";
	key_names[sf::Keyboard::Up] = "Up";
	key_names[sf::Keyboard::Down] = "Down";
	key_names[sf::Keyboard::Right] = "Right";
	key_names[sf::Keyboard::Numpad1] = "Numpad1";
	key_names[sf::Keyboard::Numpad2] = "Numpad2";
	key_names[sf::Keyboard::Numpad3] = "Numpad3";
	key_names[sf::Keyboard::Numpad4] = "Numpad4";
	key_names[sf::Keyboard::Numpad5] = "Numpad5";
	key_names[sf::Keyboard::Numpad6] = "Numpad6";
	key_names[sf::Keyboard::Numpad7] = "Numpad7";
	key_names[sf::Keyboard::Numpad8] = "Numpad8";
	key_names[sf::Keyboard::Numpad9] = "Numpad9";
	key_names[sf::Keyboard::Numpad0] = "Numpad0";
	key_names[sf::Keyboard::Divide] = "Divide";
	key_names[sf::Keyboard::Multiply] = "Multiply";
	key_names[sf::Keyboard::Subtract] = "Subtract";
	key_names[sf::Keyboard::Add] = "Add";
}