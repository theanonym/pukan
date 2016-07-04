#include "pukan/core/services/resources.hpp"
#include "pukan/core/services/config.hpp"
#include "json/jparser.hpp"
#include "json/jobject.hpp"

namespace pukan {

sf::Texture * Resources::loadTexture(const std::string & name,
                                     const bfs::path & path)
{
   sf::Texture * texture = new sf::Texture;
   assert(texture->loadFromFile(path.string()));

   texture->setSmooth(true);
//   texture->setRepeated(true);

   _textures[name] = std::unique_ptr<sf::Texture>(texture);

   return texture;
}

sf::Font * Resources::loadFont(const std::string & name,
                               const bfs::path & path)
{
   sf::Font * font = new sf::Font;
   assert(font->loadFromFile(path.string()));

   _fonts[name] = std::unique_ptr<sf::Font>(font);

   return font;
}

sf::Sound * Resources::loadSound(const std::string & name,
                                 const bfs::path & path)
{
   std::unique_ptr<sf::SoundBuffer> soundBuffer(new sf::SoundBuffer);
   assert(soundBuffer->loadFromFile(path.string()));

   sf::Sound * sound = new sf::Sound(*soundBuffer);

   _soundBuffers[name] = std::move(soundBuffer);
   _sounds[name] = std::unique_ptr<sf::Sound>(sound);

   return sound;
}

sf::Shader * Resources::loadShader(const std::string & name,
                                   const bfs::path & path,
                                   sf::Shader::Type type)
{
   sf::Shader * shader = new sf::Shader;
   assert(shader->loadFromFile(path.string(), type));

   _shaders[name] = std::unique_ptr<sf::Shader>(shader);

   return shader;
}

void Resources::loadFromJson(const bfs::path & path)
{
   json::Parser parser;
   parser.readFile(path.string());
   const json::Object & root = parser.getRoot();

   for(const auto & pair : root.get("textures").getHash())
      loadTexture(pair.first, Config::get().workingDir / pair.second.get<std::string>());

   for(const auto & pair : root.get("fonts").getHash())
      loadFont(pair.first, Config::get().workingDir / pair.second.get<std::string>());

   for(const auto & pair : root.get("sounds").getHash())
      loadSound(pair.first, Config::get().workingDir / pair.second.get<std::string>());
}

void Resources::preloadFont(const std::string & name, unsigned charSize)
{
   sf::Text tmp("x", *getFont(name),  charSize);
   tmp.setStyle(sf::Text::Bold);
   YOBA_UNUSED(tmp);
}

sf::Texture * Resources::getTexture(const std::string & name)
{
   auto it = _textures.find(name);
   if(it == _textures.end())
      ythrow(std::runtime_error, "Текстура " << name << " не найдена.");
   return it->second.get();
}

sf::Font * Resources::getFont(const std::string & name)
{
   auto it = _fonts.find(name);
   if(it == _fonts.end())
      ythrow(std::runtime_error, "Шрифт " << name << " не найден.");
   return it->second.get();
}

sf::Sound * Resources::getSound(const std::string & name)
{
   auto it = _sounds.find(name);
   if(it == _sounds.end())
      ythrow(std::runtime_error, "Звук " << name << " не найден.");
   return it->second.get();
}

sf::Shader * Resources::getShader(const std::string & name)
{
   auto it = _shaders.find(name);
   if(it == _shaders.end())
      ythrow(std::runtime_error, (b::format("Шейдер `%1%' не найден.") % name).str());
   return it->second.get();
}

const std::string & Resources::getTextureName(const sf::Texture * texture)
{
   for(const auto & pair : _textures)
      if(pair.second.get() == texture)
         return pair.first;
   assert(false);
}

}
