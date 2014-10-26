#include "Graphics.h"
using namespace BitEngine;

Graphics::Graphics()
{
	// DEBUG REASONS
	unsigned int x = 800;
	unsigned int y = 600;
	bool fullscreen = false;
	// EO DEBUG REASONS
	u_window = new Window(x, y, fullscreen);
	u_gui = new GUI();
}


Graphics::~Graphics()
{
	delete u_window;
	delete u_gui;
}


void Graphics::update(const long & delta_t)
{
	u_window->xx_sfml_window()->clear(sf::Color::Black);
	/*
	 * A nice place to render everything
	*/

	// render GUI here
	
	u_window->xx_sfml_window()->display();
}


void Graphics::draw()
{
	u_gui->draw();
}

void Graphics::draw_object(sf::Drawable * drawable_object)
{
	u_window->xx_sfml_window()->draw(*drawable_object);
}


void Graphics::reset_gui()
{
	delete u_gui;
	u_gui = new GUI();
}


Window::Window(unsigned int x, unsigned int y, bool fullscreen)
{
	sf::Uint32 settings;
	if (fullscreen) settings = sf::Style::Fullscreen;
	else settings = sf::Style::Close;
	sfml_window = new sf::RenderWindow(sf::VideoMode(x, y), "BitConflict", settings);

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
