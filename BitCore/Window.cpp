#include "Window.h"
using namespace BitEngine;

Window::Window(unsigned int x, unsigned int y, bool fullscreen)
{
	sf::Uint32 settings;
	if (fullscreen) settings = sf::Style::Fullscreen;
	else settings = sf::Style::Close;
	sfml_window = new sf::RenderWindow(sf::VideoMode(x, y), "BitCore", settings);

	this->x = x;
	this->y = y;
	this->fullscreen = fullscreen;
}


Window::~Window()
{
	delete sfml_window;
}


void Window::turn_full_screen() {
	if (!fullscreen)
	{
		sfml_window->create(sf::VideoMode(x, y), "BitConflict", sf::Style::Fullscreen);
		fullscreen = true;

		g_logger->debug("Window switched to Full Screen");
	}
}


void Window::turn_windowed()
{
	if (fullscreen)
	{
		sfml_window->create(sf::VideoMode(x, y), "BitConflict", sf::Style::Close);
		fullscreen = false;

		g_logger->debug("Window switched to Windowed");
	}
}


void Window::resize(const sf::Vector2u size)
{
	if (size.x < 8192 && size.y < 4096 && size.x > 512 && size.y > 256)
		sfml_window->setSize(sf::Vector2u(size.x, size.y));
	x = size.x;
	y = size.y;
}


bool Window::is_fullscreen()
{
	return fullscreen;
}


sf::Vector2u Window::get_xy() const
{
	return sf::Vector2u(x, y);
}


sf::RenderWindow * Window::xx_sfml_window()
{
	return sfml_window;
}
