#include "GUI.h"
#include "BitCore.h"
using namespace BitEngine;

GUI::GUI()
{
	// setting default values
	visible = true;
	active_color = sf::Color();
	active_font_name = "default";
}


GUI::~GUI()
{
	// deleting all layers
	for (auto it = layers.begin(); it != layers.end(); it++)
	{
		delete (*it);
	}
	layers.clear();
}


void GUI::update(const long & delta_t)
{
	// updating all layers
	for (auto it = layers.begin(); it != layers.end(); it++)
	{
		(*it)->update(delta_t);
	}
}


void GUI::set_visible(bool visible)
{
	this->visible = visible;
}


bool GUI::is_visible()
{
	return visible;
}


void GUI::draw()
{
	for (auto it = layers.begin(); it != layers.end(); it++)
	{
		(*it)->draw();
	}
}


GUILayer::GUILayer()
{
	visible = true;
}


GUILayer::~GUILayer()
{
	for (auto &it : gui_objects)
	{
		delete it;
	}
	gui_objects.clear();
}


GUILayer * GUI::add_top_layer()
{
	GUILayer * fresh = new GUILayer();
	layers.push_back(fresh);
	return fresh;
}


GUILayer * GUI::add_bottom_layer()
{
	GUILayer * fresh = new GUILayer();
	layers.push_front(fresh);
	return fresh;
}


GUILayer * GUI::add_layer_after(GUILayer * layer)
{
	GUILayer * fresh = new GUILayer();
	bool added = false;
	for (auto it = layers.begin(); it != layers.end(); it++){
		if (*it == layer)
		{
			layers.insert(++it, fresh);
			added = true;
			break;
		}
	}
	if (!added)
	{
		g_logger->warn("Could not find layer to add after");
		layers.push_back(fresh);
	}
	return fresh;
}

void GUI::remove_layer(GUILayer * layer)
{
	delete layer;
	layers.remove(layer);
}


void GUI::set_active_font(const std::string & font)
{
	active_font_name = font;
}

void GUI::set_active_color(const sf::Color & color)
{
	active_color = color;
}


void GUILayer::update(const long & delta_t)
{
	for (auto it = gui_objects.begin(); it != gui_objects.end(); it ++)
	{
		(*it)->update(delta_t);
	}
}


void GUILayer::draw()
{
	for (auto it = gui_objects.begin(); it != gui_objects.end(); it++)
	{
		(*it)->draw();
	}
}


void GUILayer::add_object(GUIObject * gobj)
{
	gui_objects.push_back(gobj);
}

void GUILayer::remove_object(GUIObject * gobj)
{
	delete gobj;
	gui_objects.remove(gobj);
}


GUIObject::GUIObject()
{
	origin = sf::Vector2u();
	rotation = 0.0f;
}


GUIObject::~GUIObject()
{
	objects.clear();
}


void GUIObject::set_active(bool active)
{
	this->active = active;
}


bool GUIObject::is_active()
{
	return active;
}


void GUIObject::set_visible(bool visible)
{
	this->visible = visible;
}


bool GUIObject::is_visible()
{
	return visible;
}


void GUIObject::set_coordinates(const sf::Vector2u & coords)
{
	origin = coords;
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		(*it)->set_origin(sf::Vector2f(origin));
	}
}


void GUIObject::move_by(const sf::Vector2u & offset)
{
	origin += offset;
	set_coordinates(origin);
}


sf::Vector2u GUIObject::get_coordinates() const
{
	return origin;
}


void GUIObject::set_rotation(float rotation)
{
	rotate(rotation - this->rotation);
}


void GUIObject::rotate(float offset)
{
	rotation += offset;
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		(*it)->rotate(offset);
	}
}


float GUIObject::get_rotation()
{
	return rotation;
}


void GUIObject::add_object(Object2D * obj)
{
	objects.push_back(obj);
}


void GUIObject::update(const long & delta_t)
{
	for (auto it = objects.begin(); it != objects.end(); it ++ )
	{
		(*it)->update(delta_t);
	}
}
void GUIObject::draw()
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		g_game->graphics->draw_object(*it);
	}
}