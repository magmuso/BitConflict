#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Logger.hpp"
#include "ResourceManager.h"

#define DEFAULT_ANIMATION_INTERVAL 1000

namespace BitEngine {

	class Object2D : virtual public sf::Drawable
	{
	public:
		Object2D();
		virtual ~Object2D();
		void add_effect(const std::string & effect_name);
		virtual void update(const long & delta_t);

		void set_origin(const sf::Vector2f & origin);
		const sf::Vector2f & get_origin() const;

		void set_position(const sf::Vector2f & position);
		const sf::Vector2f & get_position() const;

		void set_rotation(float rotation);
		float get_rotation() const;

		void set_scale(const sf::Vector2f & factors);
		const sf::Vector2f & get_scale() const;

		void move(const sf::Vector2f & offset);
		void rotate(float rotation);
		void scale(const sf::Vector2f & factor);

	protected:
		virtual sf::Transformable * get_transformable() const = 0;

		std::vector<std::string> effects;
	};

	class BitText : public Object2D
	{
	public:
		BitText();
		BitText(const std::string & text);
		BitText(const std::string & text, unsigned int size);
		virtual ~BitText();

		void set_text(const std::string & text);
		void set_size(unsigned int size);

		std::string get_text() const;
		unsigned int get_size();

		// these two should already have rendering fonts activated
		void change_font();
		void change_color();
	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
		virtual sf::Transformable * get_transformable() const;
		sf::Text sfml_text;
	};


	class BitSprite : public Object2D
	{
	public:
		BitSprite();

		// Binds BitTexture and sets size to automatic
		BitSprite(const std::string & texture_name);
		BitSprite(const std::string & texture_name, const sf::Vector2f & size);

		~BitSprite();

		void set_texture(const std::string & texture_name);
		std::string get_texture() const;

		void set_color(sf::Color & color);

		virtual void animate(const long & delta_t);

		sf::Color get_color() const;
	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
		virtual sf::Transformable * get_transformable() const;
		virtual void update(const long & delta_t);
		sf::RectangleShape sprite;
		BitTexture * texture;
		std::string texture_name;
	};

	class BitAnimatedSprite : public BitSprite
	{
	public:
		class AnimProps {
		public:
			AnimProps();
			AnimProps(long interval);
			void set_interval(long milisec);
			long get_interval();

			void set_animation_counts(unsigned int * animation_vector_info, unsigned int length);
			int get_length(unsigned int anim_row);

		private:
			long anim_interval; // speed of the animation (interchange rate)
			std::vector<unsigned int> lengths;
		};

		BitAnimatedSprite(BitTexture * texture, const sf::Vector2u & size, AnimProps & props);
		~BitAnimatedSprite();

		void stop_anim(const sf::Vector2u & frame_place);
		void stop_anim();

		void continue_anim(const sf::Vector2u & frame_place);
		void continue_anim();

		virtual void animate(const long & delta_t);

		sf::Vector2u get_current_frame() const;

	private:
		void next_frame();
		void set_frame(const sf::Vector2u & frame);

		AnimProps props;
		long counter;
		bool animated;
		sf::Vector2u current_frame;
		sf::Vector2u frame_size;
	};
};