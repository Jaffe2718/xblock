/**
 * @File: units/ui.h
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: To draw the UI of the game by current status.
 * */

#ifndef XBLOCK_UI_H
#define XBLOCK_UI_H

#include "topology.h"
#include "resources.h"

namespace xblock {

    /**
     * @brief The status of the UI.
     * */
    enum UI_Status {
        HOME,
        THREE,
        FOUR,
        FIVE,
        WIN,
        HELP,
        QUIT    // quit the game, no ui
    };

    std::string _format_time(double time);

    /**
     * @brief Draw the UI of the game.
     * @param window The window to draw the UI.
     * @param ui_status The status of the UI.
     * @param data The matrix data.
     * @param rule The rule for the matrix data.
     * @param clock The clock to calculate the time.
     * @param win_time The time when the player wins.
     * */
    void ui(sf::RenderWindow &window, UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule, sf::Clock &clock, sf::Time &win_time);

    /**
     * @brief Draw the home page of the game. Called in the ui() function.
     * @param window The window to draw the UI.
     * */
    void _ui_home(sf::RenderWindow &window);

    /**
     * @brief Draw the menu of the game. Called in the ui() function.
     * @param window The window to draw the UI.
     * @param clock The clock to calculate the time.
     * */
    void _ui_menu(sf::RenderWindow &window, sf::Clock &clock);

    /**
     * @brief Draw the matrix data of the game. Called in the ui() function.
     * @param window The window to draw the UI.
     * @param data The matrix data.
     * */
    void _ui_3x3(sf::RenderWindow &window, std::vector<int> &data);

    /**
     * @brief Draw the matrix data of the game. Called in the ui() function.
     * @param window The window to draw the UI.
     * @param data The matrix data.
     * */
    void _ui_4x4(sf::RenderWindow &window, std::vector<int> &data);

    /**
     * @brief Draw the matrix data of the game. Called in the ui() function.
     * @param window The window to draw the UI.
     * @param data The matrix data.
     * */
    void _ui_5x5(sf::RenderWindow &window, std::vector<int> &data);

    /**
     * @brief Draw the win page of the game. Called in the ui() function.
     * @param window The window to draw the UI.
     * @param win_time The time when the player wins.
     * */
    void _ui_win(sf::RenderWindow &window, sf::Time &win_time);

    /**
     * @brief Draw the help page of the game. Called in the ui() function.
     * @param window The window to draw the UI.
     * */
    void _ui_help(sf::RenderWindow &window);

} // namespace xblock

#endif //XBLOCK_UI_H
