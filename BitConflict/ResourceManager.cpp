#include "ResourceManager.h"
using namespace BitEngine;

BitTexture::BitTexture() : sf::Texture()
{
	create(0,0);
	// left as a default constructor
}


BitTexture::~BitTexture()
{
	// Left as a default destructor
}


BitTexture::BitTexture(const std::string & filename)
{
	if (!loadFromFile(filename))
	{
		create(0, 0);
		g_logger->error("Could not load Texture '" + filename + "'");
	}
}


BitTexture::BitTexture(const void * data, size_t size)
{
	if (!loadFromMemory(data, size))
	{
		g_logger->error("Could not load texture from memory");
	}
}


const sf::Vector2u & BitTexture::get_size() const
{
	return getSize();
}


ResourceManager::ResourceManager()
{
	// Left as a default empty constructor
}


ResourceManager::~ResourceManager()
{
	// let us delete all resources here
	for (auto it = fonts.begin(); it != fonts.end(); it++)
	{
		delete (it->second);
	}
	fonts.clear();

	for (auto it = shaders.begin(); it != shaders.end(); it++)
	{
		delete (it->second);
	}
	shaders.clear();

	for (auto it = textures.begin(); it != textures.end(); it++)
	{
		delete (it->second);
	}
	textures.clear();
}


void ResourceManager::load_texture(const std::string & name, const std::string & filename)
{
	auto new_texture = new BitTexture(filename);
	textures[name] = new_texture;
}


void ResourceManager::load_font(const std::string & name, const std::string & filename)
{
	auto new_font = new sf::Font();
	if (new_font->loadFromFile(filename))
	{
		fonts[name] = new_font;
	}
	else
	{
		g_logger->error("Failed to load font '" + name + "'");
	}
}


void ResourceManager::load_shader(const std::string & name, const std::string & vertex_filename, const std::string & fragment_filename)
{
	auto new_shader = new sf::Shader();
	if (new_shader->loadFromFile(vertex_filename, fragment_filename))
	{
		shaders[name] = new_shader;
	}
	else
	{
		g_logger->error("Failed to load shader");
	}
}


void ResourceManager::release_texture(const std::string & name)
{
	if (textures.find(name) != textures.end())
	{
		auto texture = textures[name];
		delete texture;
		textures.erase(name);
	}
	else
	{
		g_logger->warn("Texture '" + name + "' does not exists to delete");
	}
}


void ResourceManager::release_font(const std::string & name)
{
	if (fonts.find(name) != fonts.end())
	{
		auto font = fonts[name];
		delete font;
		fonts.erase(name);
	}
	else
	{
		g_logger->warn("Font '" + name + "' does not exists to delete");
	}
}


void ResourceManager::release_shader(const std::string & name)
{
	if (shaders.find(name) != shaders.end())
	{
		auto shader = shaders[name];
		delete shader;
		shaders.erase(name);
	}
	else
	{
		g_logger->warn("Shader '" + name + "' does not exists to delete");
	}
}