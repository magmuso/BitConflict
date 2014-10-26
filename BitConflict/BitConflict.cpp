#include "BitConflict.h"
#include "UtilExport.hpp"
using namespace BitEngine;

BitConflict::BitConflict()
{
	u_graphics = new Graphics();
	u_input = new Input();
}

void BitConflict::init()
{
	auto exporter = LuaController();
	exporter.export();
}

void BitConflict::loop()
{
	auto window = u_graphics->u_window;
	auto sfml_window = window->xx_sfml_window();

	sf::Clock tick_clock = sf::Clock();

	long mili_time = 0;
	
	while (sfml_window->isOpen())
	{
		u_input->update();

		u_graphics->update(mili_time);
		u_graphics->draw();

		// update the game clock
		mili_time = tick_clock.getElapsedTime().asMilliseconds();
		tick_clock.restart();
	}
}

BitConflict::~BitConflict()
{
}

int main()
{
	g_game = new BitEngine::BitConflict();
	g_game->init();
	g_game->loop();

	// release the global resources
	delete g_game;
	delete g_logger;
}

// GLOBALS
// be careful to initialize first __always__
BitEngine::BitConflict * BitEngine::g_game = nullptr;
Logger * g_logger = new Logger();