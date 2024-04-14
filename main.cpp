/**
 * @File: main.cpp
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: The main file of the Block Transform game. The player needs to click the number to transform the block to the correct order.
 * @Repository: https://github.com/Jaffe2718/xblock
 * @Email: 202130163019@hunnu.edu.cn
 * @License: GPL-3.0 License
 * */

#include "units/event_handling.h"

/**
 * @brief The main function of the game.
 *
 * @param argc: the number of arguments
 * @param argv: the arguments
 * @return: 0
 */
int main([[maybe_unused]] int argc, char* argv[]) {
    std::string exeDir = std::filesystem::path(argv[0]).parent_path().string();   // get the directory of the executable file

    xblock::load_resources(exeDir);                                                      // load the resources of the game
    sf::RenderWindow window(sf::VideoMode(600, 800), L"Block Transform", sf::Style::Titlebar | sf::Style::Close);
    window.setIcon(xblock::icon.getSize().x, xblock::icon.getSize().y, xblock::icon.getPixelsPtr());  // set icon
    xblock::music.play();  // play the music

    // game data variables
    xblock::UI_Status ui_status = xblock::UI_Status::HOME;                               // current ui status
    std::vector<int> data;                                                               // data of the game
    std::unordered_map<int, int> rule;                                                   // position of the game
    sf::Time win_time;                                                                   // time of winning
    sf::Clock clock;                                                                     // timer of the game

    while (window.isOpen()) {                                                            // main loop
        sf::Event event{};
        while (window.pollEvent(event)) {                                             // event loop
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                xblock::handleEvent(ui_status, data, rule, clock, win_time, event);
            }
        }
        xblock::ui(window, ui_status, data, rule, clock, win_time);
        window.display();
    }
    return 0;
}
