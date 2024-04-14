/**
 * @File: units/event_handling.h
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: The event handling of the Block Transform game. To handle the mouse click event and update the game status.
 * */

#ifndef XBLOCK_EVENT_HANDLING_H
#define XBLOCK_EVENT_HANDLING_H

#include <SFML/Graphics.hpp>
#include "ui.h"

namespace xblock {

    /**
     * @brief Handle the home event. This function is called in xblock::handleEvent().
     * @param ui_status The current status of the game.
     * @param data The matrix data of the game in std::vector<int> type.
     * @param rule The rule for the matrix data in std::unordered_map<int, int> type.
     * @param clock The clock of the game.
     * @param mouseX The x coordinate of the mouse.
     * @param mouseY The y coordinate of the mouse.
     * */
    void _handleMenu(UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule, sf::Clock &clock, int mouseX, int mouseY);

    /**
     * @brief Handle the home event. This function is called in xblock::handleEvent().
     * @param ui_status The current status of the game.
     * @param data The matrix data of the game in std::vector<int> type.
     * @param rule The rule for the matrix data in std::unordered_map<int, int> type.
     * @param clock The clock of the game.
     * @param mouseX The x coordinate of the mouse.
     * @param mouseY The y coordinate of the mouse.
     * */
    void _handleHome(UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule, sf::Clock &clock, int mouseX, int mouseY);

    /**
     * @brief Handle the 3x3 game event. This function is called in xblock::handleEvent().
     * @param ui_status The current status of the game.
     * @param data The matrix data of the game in std::vector<int> type.
     * @param rule The rule for the matrix data in std::unordered_map<int, int> type.
     * @param clock The clock of the game.
     * @param winTime The time when the player wins.
     * @param mouseX The x coordinate of the mouse.
     * @param mouseY The y coordinate of the mouse.
     * */
    void _handle3x3(UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule, sf::Clock &clock, sf::Time &winTime, int mouseX, int mouseY);

    /**
     * @brief Handle the 4x4 game event. This function is called in xblock::handleEvent().
     * @param ui_status The current status of the game.
     * @param data The matrix data of the game in std::vector<int> type.
     * @param rule The rule for the matrix data in std::unordered_map<int, int> type.
     * @param clock The clock of the game.
     * @param winTime The time when the player wins.
     * @param mouseX The x coordinate of the mouse.
     * @param mouseY The y coordinate of the mouse.
     * */
    void _handle4x4(UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule, sf::Clock &clock, sf::Time &winTime, int mouseX, int mouseY);

    /**
     * @brief Handle the 5x5 game event. This function is called in xblock::handleEvent().
     * @param ui_status The current status of the game.
     * @param data The matrix data of the game in std::vector<int> type.
     * @param rule The rule for the matrix data in std::unordered_map<int, int> type.
     * @param clock The clock of the game.
     * @param winTime The time when the player wins.
     * @param mouseX The x coordinate of the mouse.
     * @param mouseY The y coordinate of the mouse.
     * */
    void _handle5x5(UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule, sf::Clock &clock, sf::Time &winTime, int mouseX, int mouseY);

    /**
     * @brief Handle the win event. This function is called in xblock::handleEvent().
     * @param ui_status The current status of the game.
     * @param winTime The time when the player wins.
     * */
    void _handleWin(UI_Status &ui_status, sf::Time &winTime);

    /**
     * @brief Handle the help event. This function is called in xblock::handleEvent().
     * @param ui_status The current status of the game.
     * */
    void _handleHelp(UI_Status &ui_status);

    /**
     * @brief Handle the mouse click event.
     * @param ui_status The current status of the game.
     * @param data The matrix data of the game in std::vector<int> type.
     * @param rule The rule for the matrix data in std::unordered_map<int, int> type.
     * @param clock The clock of the game.
     * @param winTime The time when the player wins.
     * @param event The event of the game.
     * */
    void handleEvent(UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule, sf::Clock &clock, sf::Time &winTime, sf::Event &event);

} // namespace xblock

#endif //XBLOCK_EVENT_HANDLING_H
