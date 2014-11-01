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
			export_input();
			export_resource_manager();
			export_gui();
		}

		
		void run_main()
		{
			lua->LoadStandardLibraries();

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

		LuaTable color_to_table(const Color & color)
		{
			auto color_table = lua->CreateTable();
			color_table.Set("r", color.r); color_table.Set("g", color.g);
			color_table.Set("b", color.b); color_table.Set("a", color.a);
			return color_table;
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


		void export_input()
		{

			auto input = g_game->u_input;
			auto global = lua->GetGlobalEnvironment();
			auto keyboard_keys = lua->CreateTable();

			for (int i = 0; i < sf::Keyboard::KeyCount; i++)
			{
				keyboard_keys.Set(input->get_key_name((sf::Keyboard::Key)i), i);
			}
			
			global.Set("KeyboardsKeys", keyboard_keys);
			global.Set("is_key_pressed", lua->CreateFunction<bool(int)>(
				[&](int key) {
					return input->is_key_pressed((sf::Keyboard::Key)key);
				}
			));
			global.Set("is_key_typed", lua->CreateFunction<bool(int)>(
				[&](int key) {
					return input->is_key_typed((sf::Keyboard::Key)key);
				}
			));
			global.Set("get_local_mouse_position", lua->CreateFunction<LuaTable()>(
				[&]() {
					return vector_to_table(input->get_local_mouse_position());
				}
			));
			global.Set("get_global_mouse_position", lua->CreateFunction<LuaTable()>(
				[&]() {
					return vector_to_table(input->get_global_mouse_position());
				}
			));
			global.Set("is_mouse_button_pressed", lua->CreateFunction<bool(int)>(
				[&](int button){
					if (button < 0 || button > 2) return false;
					else return input->is_mouse_button_pressed((sf::Mouse::Button)button);
				}
			));
		}


		void export_resource_manager()
		{
			auto global = lua->GetGlobalEnvironment();

			auto res_man = g_game->u_res_man;

			auto load_texture = lua->CreateFunction<void(const std::string, const std::string)>(
				[&](const std::string name, const std::string filename)
			{
				res_man->load_texture(name, filename);
			});
/*			auto load_font = lua->CreateFunction<void(std::string, std::string)>(
				std::bind(&ResourceManager::load_font, res_man));
			auto load_shader = lua->CreateFunction<void(std::string, std::string, std::string)>(
				std::bind(&ResourceManager::load_shader, res_man));
			auto release_texture = lua->CreateFunction<void(std::string)>(
				std::bind(&ResourceManager::release_texture, res_man));
			auto release_font = lua->CreateFunction<void(std::string)>(
				std::bind(&ResourceManager::release_font, res_man));
			auto release_shader = lua->CreateFunction<void(std::string)>(
				std::bind(&ResourceManager::release_shader, res_man));

			global.Set("load_texture", load_texture);
			global.Set("load_font", load_font);
			global.Set("load_shader", load_shader);
			global.Set("release_texture", release_texture);
			global.Set("release_font", release_font);
			global.Set("release_shader", release_shader);*/
		}

		void export_2d()
		{
			auto global = lua->GetGlobalEnvironment();
			auto res_man = g_game->u_res_man;
			
			//auto sprite2d = lua->CreateUserdata<BitSprite>(new BitSprite());
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