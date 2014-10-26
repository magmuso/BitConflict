#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "GUI.h"

namespace BitEngine{
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


	class Graphics : sf::NonCopyable
	{
	public:
		// everything that has to do with graphics goes here
		Graphics();
		~Graphics();

		void update(const long & delta_t);
		void draw();
		void draw_object(sf::Drawable * drawable_object);
		void reset_gui();

		// main control window; only one supported at the moment
		Window * u_window;
		GUI * u_gui;
	};
};

