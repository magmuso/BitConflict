#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Clock.hpp>

#include "Logger.hpp"
#include "Graphics.h"
#include "Input.h"

namespace BitEngine{
	class BitCore : sf::NonCopyable
	{
	public:
		BitCore();
		~BitCore();
		
		Graphics * graphics;
		Input * input;
		ResourceManager * res_man;

		void init();
		void loop();
	};
	extern BitCore * g_game;
};
