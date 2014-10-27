#include "ResourceManager.h"
using namespace BitEngine;

BitTexture::BitTexture()
{
	sf::Texture::create(0,0);
	// TODO: implement
}


BitTexture::~BitTexture()
{
	// TODO: implement
}


BitTexture::BitTexture(const std::string & filename)
{
	// TODO: implement
}


const sf::Vector2u & BitTexture::get_size() const
{
	return getSize();
}


ResourceManager::ResourceManager()
{
	// TODO: implement
}


ResourceManager::~ResourceManager()
{
	// TODO: implement
}

void ResourceManager::load_texture(const std::string & name, const std::string & filename)
{
	// TODO: implement
}

void ResourceManager::load_font(const std::string & name, const std::string & filename)
{
	// TODO: implement
}