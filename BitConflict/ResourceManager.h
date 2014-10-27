#pragma once
#include <string>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace BitEngine{
	class BitTexture : public sf::Texture
	{
	public:
		BitTexture();
		~BitTexture();
		BitTexture(const std::string & filename);

		const sf::Vector2u & get_size() const;
	};


	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		void load_texture(const std::string & name, const std::string & filename);
		void load_font(const std::string & name, const std::string & filename);

	private:
		std::map<std::string, BitTexture *> textures;
		std::map<std::string, sf::Font *> fonts;
		
	};
};

