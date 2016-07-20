#include "Input.h"
#include "BitCore.h"
using namespace BitEngine;

Input::Input()
{
	_typed_keys = new bool[sf::Keyboard::KeyCount];
	_key_names = new std::string[sf::Keyboard::KeyCount];
	register_key_names();
	_input_event = sf::Event();
}


Input::~Input()
{
	delete[] _typed_keys;
}


void Input::update()
{
	memset(_typed_keys, false, sf::Keyboard::KeyCount);
	sf::RenderWindow * window = g_game->graphics->window->xx_sfml_window();
	while (window->pollEvent(_input_event))
	{
		if (_input_event.type == sf::Event::Closed)
			window->close();
		if (_input_event.type == sf::Event::KeyPressed) {
			if (_input_event.key.code == sf::Keyboard::F4 && _input_event.key.alt)
				window->close();
			_typed_keys[_input_event.key.code] = true;
		}
	}
}


bool Input::isKeyPressed(sf::Keyboard::Key key) const
{
	return sf::Keyboard::isKeyPressed(key);
}


bool Input::isKeyTyped(sf::Keyboard::Key key) const
{
	return _typed_keys[key];
}


bool Input::isMouseButtonPressed(sf::Mouse::Button button) const
{
	return sf::Mouse::isButtonPressed(button);
}


sf::Vector2i Input::getLocalMousePosition() const
{
	auto window = g_game->graphics->window->xx_sfml_window();
	return sf::Mouse::getPosition(*window);
}


sf::Vector2i Input::getGlobalMousePosition() const
{
	return sf::Mouse::getPosition();
}


const std::string Input::getKeyName(sf::Keyboard::Key key) const
{
	if (key != -1 && key < sf::Keyboard::KeyCount)
	{
		return _key_names[key];
	}
	else
	{
		return "Unknown Key";
	}
}


void Input::register_key_names()
{
	_key_names[sf::Keyboard::Escape] = "Escape";
	_key_names[sf::Keyboard::F1] = "F1";
	_key_names[sf::Keyboard::F2] = "F2";
	_key_names[sf::Keyboard::F3] = "F3";
	_key_names[sf::Keyboard::F4] = "F4";
	_key_names[sf::Keyboard::F5] = "F5";
	_key_names[sf::Keyboard::F6] = "F6";
	_key_names[sf::Keyboard::F7] = "F7";
	_key_names[sf::Keyboard::F8] = "F8";
	_key_names[sf::Keyboard::F9] = "F9";
	_key_names[sf::Keyboard::F10] = "F10";
	_key_names[sf::Keyboard::F11] = "F11";
	_key_names[sf::Keyboard::F12] = "F12";
	_key_names[sf::Keyboard::Insert] = "Insert";
	_key_names[sf::Keyboard::Delete] = "Delete";
	_key_names[sf::Keyboard::Home] = "Home";
	_key_names[sf::Keyboard::End] = "End";
	_key_names[sf::Keyboard::PageUp] = "PageUp";
	_key_names[sf::Keyboard::PageDown] = "PageDown";
	_key_names[sf::Keyboard::Tilde] = "Tilde";
	_key_names[sf::Keyboard::Num1] = "Num1";
	_key_names[sf::Keyboard::Num2] = "Num2";
	_key_names[sf::Keyboard::Num3] = "Num3";
	_key_names[sf::Keyboard::Num4] = "Num4";
	_key_names[sf::Keyboard::Num5] = "Num5";
	_key_names[sf::Keyboard::Num6] = "Num6";
	_key_names[sf::Keyboard::Num7] = "Num7";
	_key_names[sf::Keyboard::Num8] = "Num8";
	_key_names[sf::Keyboard::Num9] = "Num9";
	_key_names[sf::Keyboard::Num0] = "Num0";
	_key_names[sf::Keyboard::Dash] = "Dash";
	_key_names[sf::Keyboard::Equal] = "Equal";
	_key_names[sf::Keyboard::BackSpace] = "BackSpace";
	_key_names[sf::Keyboard::Tab] = "Tab";
	_key_names[sf::Keyboard::Q] = "Q";
	_key_names[sf::Keyboard::W] = "W";
	_key_names[sf::Keyboard::E] = "E";
	_key_names[sf::Keyboard::R] = "R";
	_key_names[sf::Keyboard::T] = "T";
	_key_names[sf::Keyboard::Y] = "Y";
	_key_names[sf::Keyboard::U] = "U";
	_key_names[sf::Keyboard::I] = "I";
	_key_names[sf::Keyboard::O] = "O";
	_key_names[sf::Keyboard::P] = "P";
	_key_names[sf::Keyboard::LBracket] = "LBracket";
	_key_names[sf::Keyboard::RBracket] = "RBracket";
	_key_names[sf::Keyboard::BackSlash] = "BackSlash";
	_key_names[sf::Keyboard::A] = "A";
	_key_names[sf::Keyboard::S] = "S";
	_key_names[sf::Keyboard::D] = "D";
	_key_names[sf::Keyboard::F] = "F";
	_key_names[sf::Keyboard::G] = "G";
	_key_names[sf::Keyboard::H] = "H";
	_key_names[sf::Keyboard::J] = "J";
	_key_names[sf::Keyboard::K] = "K";
	_key_names[sf::Keyboard::L] = "L";
	_key_names[sf::Keyboard::SemiColon] = "SemiColon";
	_key_names[sf::Keyboard::Quote] = "Quote";
	_key_names[sf::Keyboard::Return] = "Enter";
	_key_names[sf::Keyboard::LShift] = "LShift";
	_key_names[sf::Keyboard::Z] = "Z";
	_key_names[sf::Keyboard::X] = "X";
	_key_names[sf::Keyboard::C] = "C";
	_key_names[sf::Keyboard::V] = "V";
	_key_names[sf::Keyboard::B] = "B";
	_key_names[sf::Keyboard::N] = "N";
	_key_names[sf::Keyboard::M] = "M";
	_key_names[sf::Keyboard::Comma] = "Comma";
	_key_names[sf::Keyboard::Period] = "Period";
	_key_names[sf::Keyboard::Slash] = "Slash";
	_key_names[sf::Keyboard::RShift] = "RShift";
	_key_names[sf::Keyboard::LControl] = "LControl";
	_key_names[sf::Keyboard::LAlt] = "LAlt";
	_key_names[sf::Keyboard::Space] = "Space";
	_key_names[sf::Keyboard::RControl] = "RControl";
	_key_names[sf::Keyboard::RAlt] = "RAlt";
	_key_names[sf::Keyboard::Left] = "Left";
	_key_names[sf::Keyboard::Up] = "Up";
	_key_names[sf::Keyboard::Down] = "Down";
	_key_names[sf::Keyboard::Right] = "Right";
	_key_names[sf::Keyboard::Numpad1] = "Numpad1";
	_key_names[sf::Keyboard::Numpad2] = "Numpad2";
	_key_names[sf::Keyboard::Numpad3] = "Numpad3";
	_key_names[sf::Keyboard::Numpad4] = "Numpad4";
	_key_names[sf::Keyboard::Numpad5] = "Numpad5";
	_key_names[sf::Keyboard::Numpad6] = "Numpad6";
	_key_names[sf::Keyboard::Numpad7] = "Numpad7";
	_key_names[sf::Keyboard::Numpad8] = "Numpad8";
	_key_names[sf::Keyboard::Numpad9] = "Numpad9";
	_key_names[sf::Keyboard::Numpad0] = "Numpad0";
	_key_names[sf::Keyboard::Divide] = "Divide";
	_key_names[sf::Keyboard::Multiply] = "Multiply";
	_key_names[sf::Keyboard::Subtract] = "Subtract";
	_key_names[sf::Keyboard::Add] = "Add";
}