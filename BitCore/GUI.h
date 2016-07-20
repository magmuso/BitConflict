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

		void setActive(bool active);
		bool isActive();

		void setVisible(bool visible);
		bool isVisible();


		// this is the origin
		void setCoordinates(const sf::Vector2u & coords);
		void moveBy(const sf::Vector2u & offset);
		sf::Vector2u getCoordinates() const;

		void setRotation(float rotation);
		void rotate(float offset);
		float getRotation();

		void addObject(Object2D * obj);
		void update(const long & delta_t);
		void draw();

	private:
		std::vector<Object2D *> _objects;
		bool _active;
		bool _visible;

		sf::Vector2u _origin;
		float _rotation;
	};


	class GUILayer
	{
	public:
		GUILayer();
		~GUILayer();

		void setVisible(bool visible);
		bool isVisible();

		void update(const long & delta_t);
		void draw();

		void addObject(GUIObject * gobj);
		void removeObject(GUIObject * gobj);

	private:
		std::list<GUIObject *> _gui_objects;
		bool _visible;
	};


	class GUI : sf::NonCopyable
	{
	public:
		GUI();
		~GUI();

		void update(const long & delta_t);
		void draw();

		void setVisible(bool visible);
		bool isVisible();

		GUILayer * addTopLayer();
		GUILayer * add_bottom_layer();
		GUILayer * addLayerAfter(GUILayer *);
		
		void removeLayer(GUILayer * layer);

		void setActiveFont(const std::string & font);
		void setActiveColor(const sf::Color & color);

	private:
		std::list<GUILayer *> _layers;
		bool _visible;

		std::string _active_font_name;
		sf::Color _active_color;
	};
};
