#pragma once
#include <string>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "Logger.hpp"

namespace BitEngine{
	class BitTexture : public sf::Texture
	{
	public:
		BitTexture();
		~BitTexture();
		BitTexture(const std::string & filename);
		BitTexture(const void * data, size_t size);

		const sf::Vector2u & get_size() const;
	};


	class ResourceManager : sf::NonCopyable
	{
	public:
		ResourceManager();
		~ResourceManager();

		void load_texture(const std::string & name, const std::string & filename);
		void load_font(const std::string & name, const std::string & filename);
		void load_shader(const std::string & name, const std::string & vertex_filename, const std::string & fragment_shader);

		void release_texture(const std::string & name);
		void release_font(const std::string & name);
		void release_shader(const std::string & name);

		BitTexture * get_texture(const std::string & name);
		sf::Font * get_font(const std::string & name);
		sf::Shader * get_shader(const std::string & name);

	private:
		std::map<std::string, BitTexture *> textures;
		std::map<std::string, sf::Font *> fonts;
		std::map<std::string, sf::Shader *> shaders;
	};
};

