#pragma once
#include <list>
#include <SFML/System/NonCopyable.hpp>
#include "Logger.hpp"
#include "Object2D.h"

namespace BitEngine {
	class GUIObject
	{
	public:
		GUIObject();
		~GUIObject();

		void set_active(bool active);
		bool is_active();

		void set_visible(bool visible);
		bool is_visible();


		// this is the origin
		void set_coordinates(const sf::Vector2u & coords);
		void move_by(const sf::Vector2u & offset);
		sf::Vector2u get_coordinates() const;

		void set_rotation(float rotation);
		void rotate(float offset);
		float get_rotation();

		void add_object(Object2D * obj);
		void update(const long & delta_t);
		void draw();

	private:
		std::vector<Object2D *> objects;
		bool active;
		bool visible;

		sf::Vector2u origin;
		float rotation;
	};


	class GUILayer
	{
	public:
		GUILayer();
		~GUILayer();

		void set_visible(bool visible);
		bool is_visible();

		void update(const long & delta_t);
		void draw();

		void add_object(GUIObject * gobj);
		void remove_object(GUIObject * gobj);

	private:
		std::list<GUIObject *> gui_objects;
		bool visible;
	};


	class GUI : sf::NonCopyable
	{
	public:
		GUI();
		~GUI();

		void update(const long & delta_t);
		void draw();

		void set_visible(bool visible);
		bool is_visible();

		GUILayer * add_top_layer();
		GUILayer * add_bottom_layer();
		GUILayer * add_layer_after(GUILayer *);
		
		void remove_layer(GUILayer * layer);

	private:
		std::list<GUILayer *> layers;
		bool visible;
	};
};
