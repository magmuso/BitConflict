#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Logger.hpp"

namespace BitEngine {

// should be unique object
class Window : sf::NonCopyable
{
public:
	Window(unsigned int x, unsigned int y, bool fullscreen);
	~Window();

	void turn_full_screen();
	void turn_windowed();

	// resize
	void resize(sf::Vector2u size);

	sf::RenderWindow * xx_sfml_window();

	bool is_fullscreen();
	sf::Vector2u get_xy() const;

private:
	unsigned int x;
	unsigned int y;
	bool fullscreen;
	sf::RenderWindow * sfml_window;
};

}