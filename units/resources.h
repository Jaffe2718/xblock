/**
 * @File: units/resources.h
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: To load the resources of the game.
 * */

#ifndef XBLOCK_RESOURCES_H
#define XBLOCK_RESOURCES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace xblock{

    /**
     * @brief The arial font of the game.
     * */
    extern sf::Font arial;

    /**
     * @brief The arial bold font of the game.
     * */
    extern sf::Font arial_bold;

    /**
     * @brief The icon of the game.
     * */
    extern sf::Image icon;

    /**
     * @brief The music of the game.
     * */
    extern sf::Music music;

    /**
     * @brief Load the resources of the game. called in main.cpp at the beginning of the main function.
     * @param exeDir The directory of the executable file.
     * */
    void load_resources(const std::string& exeDir);
}

#endif //XBLOCK_RESOURCES_H
