/**
 * @File: units/resources.cpp
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: To load the resources of the game.
 * */

#include "resources.h"

sf::Font xblock::arial;
sf::Font xblock::arial_bold;
sf::Image xblock::icon;
sf::Music xblock::music;

void xblock::load_resources(const std::string& exeDir) {
    /**
     * Load the resources of the game.
     * */
    arial.loadFromFile(exeDir + "/res/arial.ttf");
    arial_bold.loadFromFile(exeDir + "/res/arialbd.ttf");
    icon.loadFromFile(exeDir + "/res/xblock.png");
    if (!music.openFromFile(exeDir + "/res/xnftj.mp3")) {
        throw std::runtime_error("Failed to load music.");
    } else {
        music.setLoop(true);
    }
}