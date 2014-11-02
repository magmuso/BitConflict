#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <luacppinterface.h>
#include "BitConflict.h"
#include <cstdarg>

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
			export_2d();
			export_gui();

			lua->RunScript("local stuff = BitSprite()\nstuff:set_texture(\"Stuff\")");
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
				[&](int button) {
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
			auto load_font = lua->CreateFunction<void(const std::string, const std::string)>(
				[&](const std::string name, const std::string filename)
			{
				res_man->load_font(name, filename);
			});
			auto load_shader = lua->CreateFunction<void(const std::string, const std::string, const std::string)>(
				[&](const std::string name, const std::string vertex_filename, const std::string fragment_filename)
			{
				res_man->load_shader(name, vertex_filename, fragment_filename);
			});
			auto release_texture = lua->CreateFunction<void(std::string)>(
				[&](const std::string name)
			{
				res_man->release_texture(name);
			});
			auto release_font = lua->CreateFunction<void(std::string)>(
				[&](const std::string name)
			{
				res_man->release_font(name);
			});
			auto release_shader = lua->CreateFunction<void(std::string)>(
				[&](const std::string name)
			{
				res_man->release_shader(name);
			});

			global.Set("load_texture", load_texture);
			global.Set("load_font", load_font);
			global.Set("load_shader", load_shader);
			global.Set("release_texture", release_texture);
			global.Set("release_font", release_font);
			global.Set("release_shader", release_shader);
		}


		template<typename T>
		void object2d_bind(LuaUserdata<T> & object2d)
		{
			object2d.Set("add_effect", lua->CreateFunction<void(const std::string)>(
				[&](const std::string name)
			{
				object2d->add_effect(name);
			}));

			object2d.Set("set_origin", lua->CreateFunction<void(float, float)>(
				[&](float x, float y)
			{
				object2d->set_origin(sf::Vector2f(x, y));
			}));

			object2d.Set("get_origin", lua->CreateFunction<LuaTable()>(
				[&]()
			{
				return vector_to_table(object2d->get_origin());
			}));

			object2d.Set("set_position", lua->CreateFunction<void(float, float)>(
				[&](float x, float y)
			{
				object2d->set_position(sf::Vector2f(x, y));
			}));
			
			object2d.Set("get_position", lua->CreateFunction<LuaTable()>(
				[&]()
			{
				return vector_to_table(object2d->get_position());
			}));

			object2d.Bind("set_rotation", &T::set_rotation);
			object2d.Bind("get_rotation", &T::get_rotation);

			object2d.Set("set_scale", lua->CreateFunction<void(float, float)>(
				[&](float x, float y)
			{
				object2d->set_scale(sf::Vector2f(x, y));
			}));

			object2d.Set("get_scale", lua->CreateFunction<LuaTable()>(
				[&]()
			{
				return vector_to_table(object2d->get_scale());
			}));

			object2d.Set("move", lua->CreateFunction<void(float, float)>(
				[&](float x, float y)
			{
				object2d->move(sf::Vector2f(x, y));
			}));

			object2d.Bind("rotate", &T::rotate);

			object2d.Set("scale", lua->CreateFunction<void(float, float)>(
				[&](float x, float y)
			{
				object2d->scale(sf::Vector2f(x, y));
			}));
		}

		template<typename T>
		void sprite2d_bind(LuaUserdata<T> sprite2d)
		{
			object2d_bind(sprite2d);
			sprite2d.Set("set_texture", lua->CreateFunction<void(const std::string)>(
				[&](const std::string & name)
			{
				sprite2d->set_texture(name);
			}));

			sprite2d.Bind("get_texture", &BitSprite::get_texture);
			sprite2d.Set("set_color", lua->CreateFunction<void(float, float, float, float)>(
				[&](float r, float g, float b, float a)
			{
				sprite2d->set_color(sf::Color(r, g, b, a));
			}));
			sprite2d.Set("get_color", lua->CreateFunction<LuaTable()>(
				[&]()
			{
				return color_to_table(sprite2d->get_color());
			}));
		}


		void export_2d()
		{
			auto global = lua->GetGlobalEnvironment();
			auto res_man = g_game->u_res_man;
			
			auto sprite2d_constructor = lua->CreateFunction<LuaUserdata<BitSprite>()>(
				[&]() -> LuaUserdata<BitSprite>
			{
				auto sprite2d = lua->CreateUserdata<BitSprite>(new BitSprite());
				sprite2d_bind(sprite2d);

				//sprite2d.Bind("set_texture", &BitSprite::set_texture);
				/*sprite2d.Set("set_texture", lua->CreateFunction<void(const std::string)>(
					[&](const std::string & texture_name)
				{
					sprite2d->set_texture(texture_name);
				}));*/
				//sprite2d.easy_bind(&BitSprite::set_texture, sprite2d.GetPointer());
				//sprite2d.easy_bind<void(const std::string)>("set_texture", &BitSprite::set_texture, sprite2d.GetPointer());
				return sprite2d;
			});
			
			auto bit_text_contructor = lua->CreateFunction<LuaUserdata<BitText>(const std::string content)>(
				[&](const std::string & content)
			{
				auto bit_text = lua->CreateUserdata<BitText>(new BitText(content));
				object2d_bind(bit_text);
				bit_text.Set("set_text", lua->CreateFunction<void(const std::string)>(
					[&](const std::string content)
				{
					bit_text->set_text(content);
				}));
				bit_text.Bind("get_text", &BitText::get_text);
				bit_text.Bind("set_size", &BitText::set_size);
				bit_text.Bind("get_size", &BitText::get_size);

				bit_text.Bind("change_font", &BitText::change_font);
				bit_text.Bind("change_color", &BitText::change_color);

				return bit_text;
			});

			global.Set("BitSprite", sprite2d_constructor);
			global.Set("BitText", bit_text_contructor);
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