#include "Camera.h"

using namespace BitCore;

Camera::Camera()
{
	_look_at = sf::Vector3f();
	_position = sf::Vector3f(0.0f, 0.0f, 1.0f);
	_rotation = 0.0f;
}


Camera::~Camera()
{
}

BitCore::Camera::Camera(const sf::Vector3f & position, const sf::Vector3f & look_at, float rotation)
{
	_position = position;
	_look_at = look_at;
	_rotation = rotation;
}

void BitCore::Camera::setRoll(float rotation)
{
	// TODO: implement
	throw;
}

void BitCore::Camera::roll(float amount)
{
}

float BitCore::Camera::getRoll()
{
	return 0.0f;
}

void BitCore::Camera::setLookAt(sf::Vector3f & look_at)
{
}

sf::Vector3f BitCore::Camera::getLookAt()
{
	return sf::Vector3f();
}

void BitCore::Camera::rotate(sf::Vector3f & angles)
{
}

void BitCore::Camera::setPosition(sf::Vector3f & look_at)
{
}

sf::Vector3f BitCore::Camera::getPosition()
{
	return sf::Vector3f();
}

void BitCore::Camera::update_gl()
{
	_look_at = _look_at.Normalize();

	gluLookAt(_position.x, _position.y, _position.z,
			  _look_at.x, _look_at.y, _look_at.z,
			  );
}
