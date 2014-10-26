#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Clock.hpp>

#include "Logger.hpp"
#include "Graphics.h"
#include "Input.h"

namespace BitEngine{
	class BitConflict : sf::NonCopyable
	{
	public:
		BitConflict();
		~BitConflict();
		
		Graphics * u_graphics;
		Input * u_input;

		void init();
		void loop();
	};
	extern BitConflict * g_game;
};
