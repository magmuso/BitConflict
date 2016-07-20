#include "BitCore.h"
using namespace BitEngine;

BitCore::BitCore()
{
	graphics = new Graphics();
	input = new Input();
	res_man = new ResourceManager();
}

void BitCore::init()
{

}

void BitCore::loop()
{
	auto window = graphics->window;
	auto sfml_window = window->xx_sfml_window();

	sf::Clock tick_clock = sf::Clock();

	long mili_time = 0;
	
	while (sfml_window->isOpen())
	{
		input->update();

		graphics->update(mili_time);
		graphics->draw();

		// update the game clock
		mili_time = tick_clock.getElapsedTime().asMilliseconds();
		tick_clock.restart();
	}
}

BitCore::~BitCore()
{
	delete graphics;
	delete input;
	delete res_man;
}

int main()
{
	g_game = new BitEngine::BitCore();
	g_game->init();
	g_game->loop();

	// release the global resources
	delete g_game;
	delete g_logger;
}

// GLOBALS
// be careful to initialize first __always__
BitEngine::BitCore * BitEngine::g_game = nullptr;
Logger * g_logger = new Logger();