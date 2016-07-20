#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Logger.hpp"
#include "ResourceManager.h"
#include <functional>
#include <exception>

#define DEFAULT_ANIMATION_INTERVAL 1000

namespace BitEngine {

	class Object2D : virtual public sf::Drawable
	{
	public:
		Object2D();
		virtual ~Object2D();
		void addEffect(const std::string & effect_name);

		void setOrigin(const sf::Vector2f & origin);
		const sf::Vector2f & getOrigin() const;

		void setPosition(const sf::Vector2f & position);
		const sf::Vector2f & getPosition() const;

		void setRotation(float rotation);
		float getRotation() const;

		void setScale(const sf::Vector2f & factors);
		const sf::Vector2f & getScale() const;

		void move(const sf::Vector2f & offset);
		void rotate(float rotation);
		void scale(const sf::Vector2f & factor);

		void setUpdateFunction(const std::function<void(const long &)> & func);

		// virtual functions
		virtual void update(const long & delta_t);

	protected:
		virtual sf::Transformable * get_transformable() const = 0;
		virtual sf::Drawable * get_drawable() const = 0;

		std::vector<std::string> _effects;

	private:
		std::function<void(const long &)> _func;
	};

	class BitText : public Object2D
	{
	public:
		BitText();
		BitText(const std::string & text);
		BitText(const std::string & text, unsigned int size);
		virtual ~BitText();

		void setText(const std::string & text);
		void setSize(unsigned int size);

		std::string getText() const;
		unsigned int getSize();

		// these two should already have rendering fonts activated
		void changeFont();
		void changeColor();
	protected:
		virtual sf::Transformable * get_transformable() const;
		virtual sf::Drawable * get_drawable() const;
		sf::Text _sfml_text;
	};


	class BitSprite : public Object2D
	{
	public:
		BitSprite();

		// Binds BitTexture and sets size to automatic
		BitSprite(const std::string & texture_name);
		BitSprite(const std::string & texture_name, const sf::Vector2f & size);

		~BitSprite();

		void setTexture(const std::string & texture_name);
		std::string getTexture() const;

		void setColor(sf::Color & color);

		sf::Color getColor() const;
	protected:
		virtual sf::Drawable * get_drawable() const;
		virtual sf::Transformable * get_transformable() const;
		sf::RectangleShape _sprite;
		BitTexture * _texture;
		std::string _texture_name;
	};

	class BitAnimatedSprite : public BitSprite
	{
	public:
		BitAnimatedSprite(const std::string & texture_name, const sf::Vector2u & size);
		BitAnimatedSprite(const std::string & texture_name, const sf::Vector2u & size, long interval);
		~BitAnimatedSprite();

		void setInterval(long milisec);
		long getInterval();

		void setAnimationCounts(unsigned int * animation_vector_info, unsigned int length);
		unsigned int getLength(unsigned int anim_row) const;

		void stopAnimAt(const sf::Vector2u & frame_place);
		void stopAnim();

		void continueAnimFrom(const sf::Vector2u & frame_place);
		void continueAnim();

		virtual void update(const long & delta_t);
		void animate(const long & delta_t);

		sf::Vector2u getCurrentFrame() const;

	private:
		void next_frame();
		void set_frame(const sf::Vector2u & frame);

		long _anim_interval; // speed of the animation (interchange rate)
		std::vector<unsigned int> _lengths;

		long _counter;
		bool _animated;
		sf::Vector2u _current_frame;
		sf::Vector2u _frame_size;
	};
};