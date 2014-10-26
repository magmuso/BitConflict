#include "Object2D.h"

using namespace BitEngine;


Object2D::Object2D()
{
	// Left empty for default constructor
}


Object2D::~Object2D()
{
	// Left empty for default destructor
}


void Object2D::add_effect(const std::string & effect_name)
{
	effects.push_back(effect_name);
}


void Object2D::update(const long & delta_t)
{
	// Left empty for default implementation
}


void Object2D::set_origin(const sf::Vector2f & origin)
{
	get_transformable()->setOrigin(origin);
}


const sf::Vector2f & Object2D::get_origin() const
{
	return get_transformable()->getOrigin();
}


void Object2D::set_position(const sf::Vector2f & position)
{
	get_transformable()->setPosition(position);
}


const sf::Vector2f & Object2D::get_position() const
{
	return get_transformable()->getPosition();
}


void Object2D::set_rotiation(float rotation)
{
	get_transformable()->setRotation(rotation);
}


float Object2D::get_rotation() const
{
	return get_transformable()->getRotation();
}


void Object2D::set_scale(const sf::Vector2f & factors)
{
	get_transformable()->setScale(factors);
}


const sf::Vector2f & Object2D::get_scale() const
{
	return get_transformable()->getScale();
}


void Object2D::move(const sf::Vector2f & offset)
{
	get_transformable()->move(offset);
}


void Object2D::rotate(float rotation)
{
	get_transformable()->rotate(rotation);
}


void Object2D::scale(const sf::Vector2f & factor)
{
	get_transformable()->scale(factor);
}


BitText::BitText()
{
	// Left empty for default constructor
}


BitText::BitText(const std::string & text)
{
	sfml_text.setString(text);
}


BitText::BitText(const std::string & text, unsigned int size)
{
	sfml_text.setString(text);
	sfml_text.setCharacterSize(size);
	auto transform = sfml_text.getTransform();
}


BitText::~BitText()
{
	delete this;
}

void BitText::change_text(const std::string & text)
{
	sfml_text.setString(text);
}


void BitText::change_size(unsigned int size)
{
	sfml_text.setCharacterSize(size);
}


std::string BitText::get_text() const
{
	return sfml_text.getString();
}


unsigned int BitText::get_size()
{
	return sfml_text.getCharacterSize();
}



// these two should already have rendering fonts activated
void BitText::change_font()
{
	//sfml_text.setFont(g_game->u_graphics->get_current_font());
	// TODO: uncomment when implemented
}


void BitText::change_color()
{
	//sfml_text.setColor(g_game->u_graphics->get_current_text_color());
	// TODO: uncomment when implemented
}


void BitText::draw(sf::RenderTarget & target, sf::RenderStates & states)
{
	dynamic_cast<sf::Drawable *>(&sfml_text)->draw(target, states);
}

sf::Transformable * BitText::get_transformable()
{
	return dynamic_cast<sf::Transformable *>(&sfml_text);
}


BitSprite::BitSprite()
{
	// left empty as default constructor
}


BitSprite::BitSprite(BitTexture * texture)
{
	sprite.setTexture(dynamic_cast<sf::Texture *>(texture));
}


BitSprite::BitSprite(BitTexture * texture, const sf::Vector2f & size)
{
	sprite.setTexture(dynamic_cast<sf::Texture *>(texture));
	sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}


BitSprite::~BitSprite()
{
	// left empty as default destructor
}


void BitSprite::set_texture(BitTexture * texture)
{
	this->texture = texture;
	sprite.setTexture(texture);
}


BitTexture * BitSprite::get_texture() const
{
	return texture;
}


void BitSprite::set_color(sf::Color & color)
{
	this->sprite.setFillColor(color);
}

void BitSprite::animate(const long & delta_t)
{
	// Left empty as default implementation of this virtual function
}


sf::Color BitSprite::get_color() const
{
	return sprite.getFillColor();
}


void BitSprite::update(const long & delta_t)
{
	animate(delta_t);
}


void BitSprite::draw(sf::RenderTarget & target, sf::RenderStates & states)
{
	dynamic_cast<sf::Drawable *>(&sprite)->draw(target, states);
}

sf::Transformable * BitSprite::get_transformable()
{
	return dynamic_cast<sf::Transformable *>(&sprite);
}


BitAnimatedSprite::AnimProps::AnimProps()
{
	anim_interval = DEFAULT_ANIMATION_INTERVAL;
}


BitAnimatedSprite::AnimProps::AnimProps(long interval)
{
	anim_interval = interval;
}


void BitAnimatedSprite::AnimProps::set_interval(long milisec)
{
	anim_interval = milisec;
}


long BitAnimatedSprite::AnimProps::get_interval()
{
	return anim_interval;
}


void BitAnimatedSprite::AnimProps::set_animation_counts(unsigned int * animation_vector_info, unsigned int lengths)
{
	for (int i = 0; i < lengths; i++)
	{
		this->lengths.push_back(animation_vector_info[i]);
	}
}


int BitAnimatedSprite::AnimProps::get_length(unsigned int anim_row)
{
	return lengths[anim_row];
}


BitAnimatedSprite::BitAnimatedSprite(BitTexture * texture, const sf::Vector2u & size, AnimProps & props)
{
	this->texture = texture;
	this->props = std::move(props);
	sprite.setTexture(texture);
	this->frame_size = size;
	counter = 0;
}


BitAnimatedSprite::~BitAnimatedSprite()
{
	// Left empty as a default destructor
}


void BitAnimatedSprite::stop_anim(const sf::Vector2u & frame_place)
{
	set_frame(frame_place);
	stop_anim();
}


void BitAnimatedSprite::stop_anim()
{
	animated = false;
	counter = 0;
}


void BitAnimatedSprite::continue_anim(const sf::Vector2u & frame_place)
{
	set_frame(frame_place);
	animated = true;
}


void BitAnimatedSprite::continue_anim()
{
	animated = true;
}


void BitAnimatedSprite::animate(const long & delta_t)
{
	counter += delta_t;
	auto interval = props.get_interval();
	while (counter / interval > 0)
	{
		next_frame();
		counter -= interval;
	}
}


sf::Vector2u BitAnimatedSprite::get_current_frame() const
{
	return current_frame;
}


void BitAnimatedSprite::set_frame(const sf::Vector2u & frame)
{
	if (texture != nullptr)
	{
		sprite.setTextureRect(sf::IntRect(frame.x * frame_size.x, frame.y * frame_size.y, frame_size.x, frame_size.y));
		current_frame = frame;
	}
	else
	{
		g_logger->warn("Texture of the animation not set");
	}
}


void BitAnimatedSprite::next_frame()
{
	auto x_frame = current_frame.x;
	if (x_frame + 1 < props.get_length(current_frame.y))
	{
		set_frame(sf::Vector2u(current_frame.x + 1, current_frame.y));
	}
	else
	{
		// bounce back to front
		set_frame(sf::Vector2u(0, current_frame.y));
	}
}