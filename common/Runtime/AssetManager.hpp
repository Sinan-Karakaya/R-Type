/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AssetManager
*/

#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#ifdef __APPLE__
    #include <sstream>
#endif

namespace RType::Runtime
{
    class AssetManager
    {
    public:
        AssetManager() = delete;

        static bool init(const std::string &projectPath = "")
        {
            if (projectPath.empty())
                return false;
            for (const auto &entry : std::filesystem::directory_iterator(projectPath + "/assets/sprites")) {
                if (entry.path().extension() == ".png") {
                    sf::Texture text;
                    if (!text.loadFromFile(entry.path().string()))
                        return false;
                    m_textures[entry.path().filename().string()] = text;
                }
            }
            for (const auto &entry : std::filesystem::directory_iterator(projectPath + "/assets/sounds")) {
#ifndef __APPLE__
                if (entry.path().extension() == ".ogg") {
                    sf::SoundBuffer soundBuffer;
                    if (!soundBuffer.loadFromFile(entry.path().string()))
                        return false;
                    m_soundBuffers[entry.path().filename().string()] = soundBuffer;
                }
#endif
            }
            for (const auto &entry : std::filesystem::directory_iterator(projectPath + "/assets/fonts")) {
                if (entry.path().extension() == ".ttf" || entry.path().extension() == ".otf") {
                    sf::Font font;
                    if (!font.loadFromFile(entry.path().string()))
                        return false;
                    m_fonts[entry.path().filename().string()] = font;
                }
            }
            for (const auto &entry : std::filesystem::directory_iterator(projectPath + "/assets/scripts")) {
                if (entry.path().extension() == ".lua") {
                    std::string script;
                    std::ifstream input(entry.path().string());
                    std::stringstream sstr;

                    while (input >> sstr.rdbuf())
                        ;
                    script = sstr.str();
                    m_scripts[entry.path().string()] = script;
                }
            }
            return true;
        }

        static void reset()
        {
            m_textures.clear();
            m_fonts.clear();
            m_scripts.clear();

#ifndef __APPLE__
            m_soundBuffers.clear();
#endif
        }

        static sf::Texture &getTexture(const std::string &path)
        {
            if (m_textures.find(path) == m_textures.end()) {
                sf::Texture texture;
                if (!texture.loadFromFile(path))
                    throw std::runtime_error("Failed to load texture: " + path);
                m_textures[path] = texture;
            }
            return m_textures[path];
        }

        static sf::Font &getFont(const std::string &path)
        {
            if (m_fonts.find(path) == m_fonts.end()) {
                sf::Font font;
                if (!font.loadFromFile(path))
                    throw std::runtime_error("Failed to load font: " + path);
                m_fonts[path] = font;
            }
            return m_fonts[path];
        }

#ifndef __APPLE__
        static sf::SoundBuffer &getSoundBuffer(const std::string &path)
        {
            if (m_soundBuffers.find(path) == m_soundBuffers.end()) {
                sf::SoundBuffer soundBuffer;
                if (!soundBuffer.loadFromFile(path))
                    throw std::runtime_error("Failed to load sound buffer: " + path);
                m_soundBuffers[path] = soundBuffer;
            }
            return m_soundBuffers[path];
        }
#endif

        static std::string &getScript(const std::string &path)
        {
            if (m_scripts.find(path) == m_scripts.end()) {
                std::string script;
                std::ifstream input(path);
                std::stringstream sstr;

                while (input >> sstr.rdbuf())
                    ;
                script = sstr.str();
                m_scripts[path] = script;
            }
            return m_scripts[path];
        }

    private:
        inline static std::unordered_map<std::string, sf::Texture> m_textures;
        inline static std::unordered_map<std::string, sf::Font> m_fonts;
        inline static std::unordered_map<std::string, std::string> m_scripts;

#ifndef __APPLE__
        inline static std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
#endif
    };
} // namespace RType::Runtime
