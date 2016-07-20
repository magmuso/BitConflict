#pragma once
#include <SFML/System/Vector3.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/OpenGL.hpp>

#ifdef WIN32
#include <gl/GLU.h>
#endif

namespace BitCore {
class Camera : sf::NonCopyable
{
public:
	Camera();
	~Camera();

	Camera(const sf::Vector3f & position, const sf::Vector3f & look_at, float rotation);

	void setRoll(float rotation);
	void roll(float amount);
	float getRoll();

	void setLookAt(sf::Vector3f & look_at);
	sf::Vector3f getLookAt();
	void rotate(sf::Vector3f & angles);
		
	void setPosition(sf::Vector3f & look_at);
	sf::Vector3f getPosition();

private:
	void update_gl();

	sf::Vector3f _look_at;
	sf::Vector3f _position;
	float _rotation;
};
}
