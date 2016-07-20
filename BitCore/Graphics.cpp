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