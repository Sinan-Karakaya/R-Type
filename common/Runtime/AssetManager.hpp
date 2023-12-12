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

namespace RType::Runtime
{
    class AssetManager
    {
    public:
        AssetManager() = delete;

        static bool init()
        {
            for (const auto &entry : std::filesystem::directory_iterator("assets/sprites")) {
                if (entry.path().extension() == ".png") {
                    sf::Font font;
                    if (!font.loadFromFile(entry.path().string()))
                        return false;
                    m_fonts[entry.path().filename().string()] = font;
                }
            }
            for (const auto &entry : std::filesystem::directory_iterator("assets/sounds")) {
                if (entry.path().extension() == ".ogg") {
                    sf::Font font;
                    if (!font.loadFromFile(entry.path().string()))
                        return false;
                    m_fonts[entry.path().filename().string()] = font;
                }
            }
            for (const auto &entry : std::filesystem::directory_iterator("assets/fonts")) {
                if (entry.path().extension() == ".ttf" || entry.path().extension() == ".otf") {
                    sf::Font font;
                    if (!font.loadFromFile(entry.path().string()))
                        return false;
                    m_fonts[entry.path().filename().string()] = font;
                }
            }
        }

        static bool reset()
        {
            m_textures.clear();
            m_fonts.clear();
            m_soundBuffers.clear();
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

    private:
        inline static std::unordered_map<std::string, sf::Texture> m_textures;
        inline static std::unordered_map<std::string, sf::Font> m_fonts;
        inline static std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    };
} // namespace RType::Runtime
