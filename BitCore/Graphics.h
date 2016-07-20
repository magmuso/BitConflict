#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Window.h"
#include "GUI.h"

namespace BitEngine{
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
		Window * window;
		GUI * gui;
	};
};

