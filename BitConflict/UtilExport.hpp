#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <luacppinterface.h>
#include "BitConflict.h"

using namespace sf;

namespace BitEngine{
	class LuaController
	{
	public:
		LuaController()
		{
			lua = new Lua();
		}


		~LuaController()
		{
			delete lua;
		}


		void export()
		{
			export_utils();
			export_gui();
		}

		
		void run_main()
		{
			lua->LoadStandardLibraries();
			std::ifstream lua_file;
			

			std::ifstream t("main.lua");
			std::string str;

			t.seekg(0, std::ios::end);
			str.reserve(t.tellg());
			t.seekg(0, std::ios::beg);

			str.assign((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());

			lua->RunScript(str);
		}


		template<typename T>
		LuaTable vector_to_table(const Vector2<T> & xy)
		{
			auto vector2_table = lua->CreateTable();
			vector2_table.Set("x", xy.x); vector2_table.Set("y", xy.y);
			return vector2_table;
		}


	private:
		Lua * lua;

		void export_utils()
		{
			auto global = lua->GetGlobalEnvironment();
			auto window = g_game->u_graphics->u_window;
			auto turn_full_screen = lua->CreateFunction<void()>(std::bind(&Window::turn_full_screen, window));
			auto turn_windowed = lua->CreateFunction<void()>(std::bind(&Window::turn_windowed, window));
			auto resize_window = lua->CreateFunction<void(int, int)>(
				[&](int x, int y){ window->resize(sf::Vector2u(x, y)); });
			auto window_xy = lua->CreateFunction<LuaTable()>(
				[&](){ return vector_to_table(window->get_xy()); });
			auto is_fullscreen = lua->CreateFunction<bool()>(std::bind(&Window::is_fullscreen, window));
			
			global.Set("turn_full_screen", turn_full_screen);
			global.Set("turn_windowed", turn_windowed);
			global.Set("resize_window", resize_window);
			global.Set("window_xy", window_xy);
			global.Set("is_fullscreen", is_fullscreen);
		}
		void export_gui()
		{
			auto global = lua->GetGlobalEnvironment();
			auto graphics = g_game->u_graphics;
			auto gui = graphics->u_gui;

			auto reset_gui = lua->CreateFunction<void()>(std::bind(&Graphics::reset_gui, graphics));

			global.Set("gui_reset", reset_gui);
		}
	};
};