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

        /**
         * @brief Initializes the AssetManager.
         * 
         * @param projectPath The path to the project directory (optional).
         * @return true if initialization is successful, false otherwise.
         */
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

        /**
         * @brief Resets the AssetManager to its initial state.
         * 
         * This function clears all the assets stored in the AssetManager and resets it to its initial state.
         * After calling this function, the AssetManager will be empty and ready to be populated with new assets.
         */
        static void reset()
        {
            m_textures.clear();
            m_fonts.clear();
            m_scripts.clear();

#ifndef __APPLE__
            m_soundBuffers.clear();
#endif
        }

        /**
         * Retrieves a reference to a texture from the asset manager.
         *
         * @param path The path to the texture file.
         * @return A reference to the requested texture.
         */
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

        /**
         * Retrieves a font from the asset manager.
         *
         * @param path The path to the font file.
         * @return A reference to the loaded font.
         */
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
        /**
         * Retrieves the sound buffer associated with the specified path.
         *
         * @param path The path of the sound buffer.
         * @return A reference to the sound buffer.
         */
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

        /**
         * @brief Retrieves the script content from the specified path.
         *
         * @param path The path to the script file.
         * @return A reference to the script content.
         */
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
