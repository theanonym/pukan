#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "pukan/common.hpp"
#include "pukan/singleton.hpp"

namespace pukan {

class Resources : public Singleton<Resources>
{
public:
   sf::Texture * loadTexture(const std::string & name, const bfs::path & path);
   sf::Font * loadFont(const std::string & name, const bfs::path & path);
   sf::Sound * loadSound(const std::string & name, const bfs::path & path);
   sf::Shader * loadShader(const std::string & name, const bfs::path & path, sf::Shader::Type type);

   void loadFromJson(const bfs::path & path);

   void preloadFont(const std::string & name, unsigned charSize);

   sf::Texture * getTexture(const std::string & name);
   sf::Font * getFont(const std::string & name);
   sf::Sound * getSound(const std::string & name);
   sf::Shader * getShader(const std::string & name);

   const std::string & getTextureName(const sf::Texture * texture);

private:
   std::unordered_map<std::string, std::unique_ptr<sf::Texture> >     _textures;
   std::unordered_map<std::string, std::unique_ptr<sf::Font> >        _fonts;
   std::unordered_map<std::string, std::unique_ptr<sf::Sound> >       _sounds;
   std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer> > _soundBuffers;
   std::unordered_map<std::string, std::unique_ptr<sf::Shader> > _shaders;
};

}

#endif // RESOURCES_HPP
