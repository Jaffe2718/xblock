# GIS软件工程上机考查——使用结构化的方法开发小游戏

202130163019 李昌哲

## 1. 项目概述
本项目开发是是一个叫Block Transform的小游戏，具体玩法如下：

```plaintext
There are 3 modes in this game: `3x3`, `4x4` and `5x5`.
You can choose the mode by clicking the corresponding button.
For each mode, all the numbers are randomly shuffled.
And in each round, if you click a block, the block will exchange it's number with the specified block.
The rules of exchange are fixed and cannot be changed in a round.
The goal of the game is to make all the numbers in order:

3x3:

1   2   3
4   5   6
7   8   9


4x4:

1   2   3   4
5   6   7   8
9   10  11  12
13  14  15  16


5x5:

1   2   3   4   5
6   7   8   9   10
11  12  13  14  15
16  17  18  19  20
21  22  23  24  25
```

## 2. 项目结构

```plaintext
.
|   CMakeLists.txt            # CMake configuration file
|   LICENSE                   # GPL-3.0 License
|   main.cpp                  # Main entry of the project & core logic module
|   README.md                 # Project README file
|
+---res                       # Resource files
|       arial.ttf             # Font file
|       arialbd.ttf           # Font file
|       res.rc                # Resource configuration file
|       xblock.ico            # Icon file to compile
|       xblock.png            # Icon file
|       xnftj.mp3             # Background music file
|
\---units
        event_handling.cpp
        event_handling.h      # Event handling module
        resources.cpp
        resources.h           # Resource loading module
        topology.cpp
        topology.h            # Data structure module
        ui.cpp
        ui.h                  # UI rendering module
```

## 3. 代码

```cpp
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
            xblock::handleEvent(ui_status, data, rule, clock, win_time, event);
        }
        xblock::ui(window, ui_status, data, rule, clock, win_time);
        window.display();
    }
    return 0;
}
```

```cpp
/**
 * @File: units/event_handling.cpp
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: The event handling of the Block Transform game. To handle the mouse click event and update the game status.
 * */

#include "event_handling.h"

void xblock::_handleMenu(xblock::UI_Status &ui_status, std::vector<int> &data,
                         std::unordered_map<int, int> &rule, sf::Clock &clock, int mouseX, int mouseY) {
    /**
     * @see xblock::_ui_menu(sf::RenderWindow &window, sf::Clock &clock)
     * There are 2 buttons:
     * 1. Home button: "Home"; 120x80; top-left: (60, 70);
     * 2. Reset button: "Reset"; 120x80; top-left: (420, 70);
     * */
    if (70 <= mouseY && mouseY <= 150) {
        if (60 <= mouseX && mouseX <= 180) {
            ui_status = xblock::UI_Status::HOME;
        } else if (420 <= mouseX && mouseX <= 540) {
            clock.restart();
            switch (ui_status) {
                case THREE:
                    data = xblock::gen_data(9);    // init data 3x3=9
                    rule = xblock::gen_rule(9);    // init rule 3x3=9
                    break;
                case FOUR:
                    data = xblock::gen_data(16);    // init data 4x4=16
                    rule = xblock::gen_rule(16);    // init rule 4x4=16
                    break;
                case FIVE:
                    data = xblock::gen_data(25);    // init data 5x5=25
                    rule = xblock::gen_rule(25);    // init rule 5x5=25
                    break;
                default:      // no other status
                    break;
            }
        }
    }
}

void xblock::_handleHome(xblock::UI_Status &ui_status, std::vector<int> &data,
                         std::unordered_map<int, int> &rule, sf::Clock &clock, int mouseX, int mouseY) {
    /**
     * @see xblock::_ui_home(sf::RenderWindow &window)
     * There are 5 buttons:
     * 1. 3x3       "3x3"; rect_size: 400x100; center:(300, 200); font_size: 28; border: 5px solid black
     * 2. 4x4       "4x4"; rect_size: 400x100; center:(300, 350); font_size: 28; border: 5px solid black
     * 3. 5x5       "5x5"; rect_size: 400x100; center:(300, 500); font_size: 28; border: 5px solid black
     * 4. Help      "?"; center:(535, 80); font_size: 24; rect_size: 70x70; border: 5px solid black
     * 5. Quit      "Quit"; rect_size: 400x100; center:(300, 650); font_size: 24; border: 5px solid black
     * */
    if (500 <= mouseX && mouseX <= 570 && 45 <= mouseY && mouseY <= 115) {
        ui_status = xblock::UI_Status::HELP;
    } else if (100 <= mouseX && mouseX <= 500) {
        clock.restart();
        if (150 <= mouseY && mouseY <= 250) {
            ui_status = xblock::UI_Status::THREE;
            data = xblock::gen_data(9);    // init data 3x3=9
            rule = xblock::gen_rule(9);    // init rule 3x3=9
        } else if (300 <= mouseY && mouseY <= 400) {
            ui_status = xblock::UI_Status::FOUR;
            data = xblock::gen_data(16);    // init data 4x4=16
            rule = xblock::gen_rule(16);    // init rule 4x4=16
        } else if (450 <= mouseY && mouseY <= 550) {
            ui_status = xblock::UI_Status::FIVE;
            data = xblock::gen_data(25);    // init data 5x5=25
            rule = xblock::gen_rule(25);    // init rule 5x5=25
        } else if (600 <= mouseY && mouseY <= 700) {
            ui_status = xblock::UI_Status::QUIT;
        }
    }
}

void xblock::_handle3x3(xblock::UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule,
                        sf::Clock &clock, sf::Time &winTime, int mouseX, int mouseY) {
    /**
     * 9 blocks: 120x120; top-left: (60 + (i % 3) * 180, 240 + (i / 3) * 180);
     * */
    _handleMenu(ui_status, data, rule, clock, mouseX, mouseY);
    for (int i = 0; i < 9; i++) {
        if (60 + (i % 3) * 180 <= mouseX && mouseX <= 180 + (i % 3) * 180 &&
            240 + (i / 3) * 180 <= mouseY && mouseY <= 360 + (i / 3) * 180) {
            xblock::transform(data, rule, i);
            if (xblock::check_win(data)) {
                winTime = clock.getElapsedTime();        // record the win time
                ui_status = xblock::UI_Status::WIN;      // switch to win status
            }
            break;
        }
    }
}

void xblock::_handle4x4(xblock::UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule,
                        sf::Clock &clock, sf::Time &winTime, int mouseX, int mouseY) {
    /**
     * 16 blocks: 100x100; top-left: (55 + (i % 4) * 130, 240 + (i / 4) * 130);
     */
    _handleMenu(ui_status, data, rule, clock, mouseX, mouseY);
    for (int i = 0; i < 16; i++) {
        if (55 + (i % 4) * 130 <= mouseX && mouseX <= 155 + (i % 4) * 130 &&
            240 + (i / 4) * 130 <= mouseY && mouseY <= 340 + (i / 4) * 130) {
            xblock::transform(data, rule, i);
            if (xblock::check_win(data)) {
                winTime = clock.getElapsedTime();        // record the win time
                ui_status = xblock::UI_Status::WIN;      // switch to win status
            }
            break;
        }
    }
}

void xblock::_handle5x5(xblock::UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule,
                        sf::Clock &clock, sf::Time &winTime, int mouseX, int mouseY) {
    /**
     * 25 blocks: 80x80; top-left: (60 + (i % 5) * 100, 240 + (i / 5) * 100)
     */
    _handleMenu(ui_status, data, rule, clock, mouseX, mouseY);
    for (int i = 0; i < 25; i++) {
        if (60 + (i % 5) * 100 <= mouseX && mouseX <= 140 + (i % 5) * 100 &&
            240 + (i / 5) * 100 <= mouseY && mouseY <= 320 + (i / 5) * 100) {
            xblock::transform(data, rule, i);
            if (xblock::check_win(data)) {
                winTime = clock.getElapsedTime();        // record the win time
                ui_status = xblock::UI_Status::WIN;      // switch to win status
            }
            break;
        }
    }
}

void xblock::_handleWin(xblock::UI_Status &ui_status, sf::Time &winTime) {
    winTime = sf::Time::Zero;
    ui_status = xblock::UI_Status::HOME;
}

void xblock::_handleHelp(xblock::UI_Status &ui_status) {
    ui_status = xblock::UI_Status::HOME;
}

void xblock::handleEvent(xblock::UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule,
                         sf::Clock &clock, sf::Time &winTime, sf::Event &event) {
    if (event.type == sf::Event::Closed) {
        ui_status = xblock::UI_Status::QUIT;
    } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        switch (ui_status) {
            case UI_Status::HOME: {
                _handleHome(ui_status, data, rule, clock, event.mouseButton.x, event.mouseButton.y);
                break;
            }
            case UI_Status::THREE: {
                _handle3x3(ui_status, data, rule, clock, winTime, event.mouseButton.x, event.mouseButton.y);
                break;
            }
            case UI_Status::FOUR: {
                _handle4x4(ui_status, data, rule, clock, winTime, event.mouseButton.x, event.mouseButton.y);
                break;
            }
            case UI_Status::FIVE: {
                _handle5x5(ui_status, data, rule, clock, winTime, event.mouseButton.x, event.mouseButton.y);
                break;
            }
            case UI_Status::WIN: {
                _handleWin(ui_status, winTime);
                break;
            }
            case UI_Status::HELP: {
                _handleHelp(ui_status);
                break;
            }
            case QUIT:  // no event handling, wait for ui to quit
                break;
        }
    }
}
```

```cpp
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
```

```cpp
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
```

```cpp
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
```

```cpp
/**
 * @File: units/topology.cpp
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: The game logic of the Block Transform game. The matrix data of the current game is stored in an array, and a directed graph is defined in a hash table to define the rules for block substitution. And encapsulated functions transform the game's matrix data based on rules and detect whether the player wins.
 * */

#include "topology.h"

std::unordered_map<int, int> xblock::gen_rule(int n) {
    /**
     * Generate a rule for a n*n game.
     * @param n: the size of the game
     * @return: a rule for the game
     */
    std::unordered_map<int, int> graph;
    std::vector<int> nodes;
    for (int i = 1; i <= n; i++) {    // init nodes = [1, 2, ..., n]
        nodes.push_back(i);
    }
    std::shuffle(nodes.begin(), nodes.end(), std::mt19937(std::random_device()()));
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(2, n);

    // main loop size between [2(include), n(include)]
    int main_loop_size = dist(gen);  //= rand() % (n - 1) + 2;

    for (int i = 0; i < main_loop_size; i++) {
        graph[nodes[i]] = nodes[(i + 1) % main_loop_size];
    }
    for (int i = main_loop_size; i < n; i++) {
        dist = std::uniform_int_distribution<int>(0, main_loop_size - 1);
        graph[nodes[i]] = nodes[dist(gen)];  // nodes[rand() % main_loop_size];
        main_loop_size++;
    }
    return graph;
}


std::vector<int> xblock::gen_data(int n) {
    /**
     * Generate data for a n*n game.
     * @param n: the size of the game
     * @return: a data for the game
     */
    std::vector<int> data;
    for (int i = 1; i <= n; i++) {
        data.push_back(i);
    }
    std::shuffle(data.begin(), data.end(), std::mt19937(std::random_device()()));
    return data;
}


void xblock::transform(std::vector<int> &data, std::unordered_map<int, int> &rule, int pos) {
    /**
     * Transform the data according to the rule.
     * @param data: the data of the game
     * @param rule: the rule of the game
     * @param pos: the position of the clicked number
     * @return: the transformed data
     */
    std::swap(data[pos], data[rule[pos + 1] - 1]);
}

bool xblock::check_win(std::vector<int> &data) {
    /**
     * data = [1, 2, 3, 4, 5, 6, 7, 8, 9 ... n] -> win
     * Check if the game is win.
     * @param data: the data of the game
     * @return: if the game is win
     */
    for (int i = 0; i < data.size(); i++) {
        if (data[i] != i + 1) {
            return false;
        }
    }
    return true;
}
```

```cpp
/**
 * @File: units/topology.h
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: The game logic of the Block Transform game. The matrix data of the current game is stored in an array, and a directed graph is defined in a hash table to define the rules for block substitution. And encapsulated functions transform the game's matrix data based on rules and detect whether the player wins.
 * */

#ifndef XBLOCK_TOPOLOGY_H
#define XBLOCK_TOPOLOGY_H

#include <bits/stdc++.h>

namespace xblock {

    /**
     * @brief Generate a random matrix data.
     * @param n The size of the matrix.
     * @return A random matrix data.
     * */
    std::vector<int> gen_data(int n);

    /**
     * @brief Generate a random rule for the matrix data.
     * @param n The size of the matrix.
     * @return A random rule for the matrix data.
     * */
    std::unordered_map<int, int> gen_rule(int n);

    /**
     * @brief Transform the matrix data based on the rule.
     * @param data The matrix data.
     * @param rule The rule for the matrix data.
     * @param pos The position of the block to be transformed.
     * */
    void transform(std::vector<int> &data, std::unordered_map<int, int> &rule, int pos);

    /**
     * @brief Check whether the player wins.
     * @param data The matrix data.
     * @return Whether the player wins.
     * */
    bool check_win(std::vector<int> &data);
}

#endif //XBLOCK_TOPOLOGY_H
```

```cpp
/**
 * @File: units/ui.cpp
 * @Author: Jaffe2718
 * @Create: 2024/4/11
 * @Description: To draw the UI of the game by current status.
 * */

#include "ui.h"

std::string xblock::_format_time(double time) {
    /**
     * Format the time to string in 00:00.000 format
     * @param time: the time in seconds
     * @return: the formatted time string
     * */
    int min = (int) time / 60;
    int sec = (int) time % 60;
    int msec = (int) (time * 1000) % 1000;
    std::string min_str = std::to_string(min);
    std::string sec_str = std::to_string(sec);
    std::string msec_str = std::to_string(msec);
    if (min_str.length() == 1) {
        min_str = "0" + min_str;
    }
    if (sec_str.length() == 1) {
        sec_str = "0" + sec_str;
    }
    if (msec_str.length() == 1) {
        msec_str = "00" + msec_str;
    } else if (msec_str.length() == 2) {
        msec_str = "0" + msec_str;
    }
    return min_str + ":" + sec_str + "." + msec_str;
}

void xblock::ui(sf::RenderWindow &window, UI_Status &ui_status, std::vector<int> &data, std::unordered_map<int, int> &rule, sf::Clock &clock, sf::Time &winTime) {
    window.clear(sf::Color::White);  // clear the window
    switch (ui_status) {
        case HOME: {
            _ui_home(window);
            break;
        }
        case THREE: {
            _ui_menu(window, clock);
            _ui_3x3(window, data);
            break;
        }
        case FOUR: {
            _ui_menu(window, clock);
            _ui_4x4(window, data);
            break;
        }
        case FIVE: {
            _ui_menu(window, clock);
            _ui_5x5(window, data);
            break;
        }
        case WIN: {
            _ui_win(window, winTime);
            break;
        }
        case HELP: {
            _ui_help(window);
            break;
        }
        case QUIT: {
            window.close();
            break;
        }
    }
}

void xblock::_ui_home(sf::RenderWindow &window) {
    /**
     * Draw the home page
     * There are 6 labels:
     * 1. title     "Block Transform"; center:(300,60); font_size: 40; bold
     * 2. 3x3       "3x3"; rect_size: 400x100; center:(300, 200); font_size: 32; border: 5px solid black
     * 3. 4x4       "4x4"; rect_size: 400x100; center:(300, 350); font_size: 32; border: 5px solid black
     * 4. 5x5       "5x5"; rect_size: 400x100; center:(300, 500); font_size: 32; border: 5px solid black
     * 5. Help      "?"; center:(535, 80); font_size: 28; rect_size: 70x70; border: 5px solid black
     * 6. Quit      "Quit"; rect_size: 400x100; center:(300, 650); font_size: 32; border: 5px solid black
    * */
    sf::Text title("Block Transform", arial_bold, 40);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setFillColor(sf::Color::Black);
    title.setPosition(300 - titleRect.width / 2, 60 - titleRect.height / 2);

    sf::RectangleShape r3x3(sf::Vector2f(400, 100));
    r3x3.setFillColor(sf::Color::Transparent);
    r3x3.setOutlineColor(sf::Color::Black);
    r3x3.setOutlineThickness(5);
    r3x3.setPosition(100, 150);
    sf::Text t3x3("3x3", arial, 32);
    sf::FloatRect t3x3Rect = t3x3.getLocalBounds();
    t3x3.setFillColor(sf::Color::Black);
    t3x3.setPosition(300 - t3x3Rect.width / 2, 200 - t3x3Rect.height);

    sf::RectangleShape r4x4(sf::Vector2f(400, 100));
    r4x4.setFillColor(sf::Color::Transparent);
    r4x4.setOutlineColor(sf::Color::Black);
    r4x4.setOutlineThickness(5);
    r4x4.setPosition(100, 300);
    sf::Text t4x4("4x4", arial, 32);
    sf::FloatRect t4x4Rect = t4x4.getLocalBounds();
    t4x4.setFillColor(sf::Color::Black);
    t4x4.setPosition(300 - t4x4Rect.width / 2, 350 - t4x4Rect.height);

    sf::RectangleShape r5x5(sf::Vector2f(400, 100));
    r5x5.setFillColor(sf::Color::Transparent);
    r5x5.setOutlineColor(sf::Color::Black);
    r5x5.setOutlineThickness(5);
    r5x5.setPosition(100, 450);
    sf::Text t5x5("5x5", arial, 32);
    sf::FloatRect t5x5Rect = t5x5.getLocalBounds();
    t5x5.setFillColor(sf::Color::Black);
    t5x5.setPosition(300 - t5x5Rect.width / 2, 500 - t5x5Rect.height);

    sf::RectangleShape rquit(sf::Vector2f(400, 100));
    rquit.setFillColor(sf::Color::Transparent);
    rquit.setOutlineColor(sf::Color::Black);
    rquit.setOutlineThickness(5);
    rquit.setPosition(100, 600);
    sf::Text tquit("Quit", arial, 32);
    sf::FloatRect tquitRect = tquit.getLocalBounds();
    tquit.setFillColor(sf::Color::Black);
    tquit.setPosition(300 - tquitRect.width / 2, 650 - tquitRect.height);

    sf::RectangleShape rhelp(sf::Vector2f(70, 70));
    rhelp.setFillColor(sf::Color::Transparent);
    rhelp.setOutlineColor(sf::Color::Black);
    rhelp.setOutlineThickness(5);
    rhelp.setPosition(500, 45);
    sf::Text thelp("?", arial, 28);
    sf::FloatRect thelpRect = thelp.getLocalBounds();
    thelp.setFillColor(sf::Color::Black);
    thelp.setPosition(535 - thelpRect.width / 2, 80 - thelpRect.height);

    window.draw(title);
    window.draw(r3x3);
    window.draw(t3x3);
    window.draw(r4x4);
    window.draw(t4x4);
    window.draw(r5x5);
    window.draw(t5x5);
    window.draw(rquit);
    window.draw(tquit);
    window.draw(rhelp);
    window.draw(thelp);
}

void xblock::_ui_menu(sf::RenderWindow &window, sf::Clock &clock) {
    /**
     * Draw the menu
     * 1. Menu rect: 520x120; top-left: (40, 50); border: 5px solid black
     * 2. Home button: "Home"; 120x80; top-left: (60, 70); border: 5px solid black
     * 3. Reset button: "Reset"; 120x80; top-left: (420, 70); border: 5px solid black
     * 4. Timer: "00:00.000"; top-left: (40, 200); font_size: 24; bold
     */
    sf::RectangleShape menu(sf::Vector2f(520, 120));
    menu.setFillColor(sf::Color::Transparent);
    menu.setOutlineColor(sf::Color::Black);
    menu.setOutlineThickness(5);
    menu.setPosition(40, 50);

    sf::RectangleShape home(sf::Vector2f(120, 80));
    home.setFillColor(sf::Color::Transparent);
    home.setOutlineColor(sf::Color::Black);
    home.setOutlineThickness(5);
    home.setPosition(60, 70);
    sf::Text thome("Home", arial_bold, 24);
    thome.setFillColor(sf::Color::Black);
    thome.setPosition(120 - thome.getLocalBounds().width / 2, 110 - thome.getLocalBounds().height);

    sf::RectangleShape reset(sf::Vector2f(120, 80));
    reset.setFillColor(sf::Color::Transparent);
    reset.setOutlineColor(sf::Color::Black);
    reset.setOutlineThickness(5);
    reset.setPosition(420, 70);
    sf::Text treset("Reset", arial_bold, 24);
    treset.setFillColor(sf::Color::Black);
    treset.setPosition(480 - treset.getLocalBounds().width / 2, 110 - treset.getLocalBounds().height);

    sf::Text timer(_format_time(clock.getElapsedTime().asSeconds()), arial_bold, 24);
    timer.setFillColor(sf::Color::Black);
    timer.setPosition(250, 90);

    window.draw(menu);
    window.draw(home);
    window.draw(thome);
    window.draw(reset);
    window.draw(treset);
    window.draw(timer);
}

void xblock::_ui_3x3(sf::RenderWindow &window, std::vector<int> &data) {
    /**
     * Draw the 3x3 grid
     9 blocks: 120x120; top-left: (60 + (i % 3) * 180, 240 + (i / 3) * 180); font_size: 32; bold
     * */

    sf::RectangleShape block[9];
    sf::Text block_text[9];
    for (int i = 0; i < 9; ++i) {
        block[i].setSize(sf::Vector2f(120, 120));
        block[i].setFillColor(sf::Color::Transparent);
        block[i].setOutlineColor(sf::Color::Black);
        block[i].setOutlineThickness(5);
        block[i].setPosition(60 + (i % 3) * 180, 240 + (i / 3) * 180);

        block_text[i].setFont(arial);
        block_text[i].setString(std::to_string(data[i]));
        block_text[i].setCharacterSize(32);
        block_text[i].setFillColor(sf::Color::Black);
        block_text[i].setPosition(120 + (i % 3) * 180 - block_text[i].getLocalBounds().width / 2,
                                  300 + (i / 3) * 180 - block_text[i].getLocalBounds().height);
    }
    for (int i = 0; i < 9; ++i) {
        window.draw(block[i]);
        window.draw(block_text[i]);
    }
}

void xblock::_ui_4x4(sf::RenderWindow &window, std::vector<int> &data) {
    /**
     * Draw the 4x4 grid
     * 16 blocks: 100x100; top-left: (55 + (i % 4) * 130, 240 + (i / 4) * 130); font_size: 32; bold
     */
    sf::RectangleShape block[16];
    sf::Text block_text[16];
    for (int i = 0; i < 16; ++i) {
        block[i].setSize(sf::Vector2f(100, 100));
        block[i].setFillColor(sf::Color::Transparent);
        block[i].setOutlineColor(sf::Color::Black);
        block[i].setOutlineThickness(5);
        block[i].setPosition(55 + (i % 4) * 130, 240 + (i / 4) * 130);

        block_text[i].setFont(arial);
        block_text[i].setString(std::to_string(data[i]));
        block_text[i].setCharacterSize(32);
        block_text[i].setFillColor(sf::Color::Black);
        block_text[i].setPosition(103 + (i % 4) * 130 - block_text[i].getLocalBounds().width / 2,
                                  290 + (i / 4) * 130 - block_text[i].getLocalBounds().height);
    }
    for (int i = 0; i < 16; ++i) {
        window.draw(block[i]);
        window.draw(block_text[i]);
    }
}

void xblock::_ui_5x5(sf::RenderWindow &window, std::vector<int> &data) {
    /**
     * Draw the 5x5 grid
     * 25 blocks: 80x80; top-left: (60 + (i % 5) * 100, 240 + (i / 5) * 100); font_size: 32; bold
     */
    sf::RectangleShape block[25];
    sf::Text block_text[25];
    for (int i = 0; i < 25; ++i) {
        block[i].setSize(sf::Vector2f(80, 80));
        block[i].setFillColor(sf::Color::Transparent);
        block[i].setOutlineColor(sf::Color::Black);
        block[i].setOutlineThickness(5);
        block[i].setPosition(60 + (i % 5) * 100, 240 + (i / 5) * 100);

        block_text[i].setFont(arial);
        block_text[i].setString(std::to_string(data[i]));
        block_text[i].setCharacterSize(32);
        block_text[i].setFillColor(sf::Color::Black);
        block_text[i].setPosition(98 + (i % 5) * 100 - block_text[i].getLocalBounds().width / 2,
                                  282 + (i / 5) * 100 - block_text[i].getLocalBounds().height);
    }
    for (int i = 0; i < 25; ++i) {
        window.draw(block[i]);
        window.draw(block_text[i]);
    }
}

void xblock::_ui_win(sf::RenderWindow &window, sf::Time &winTime) {
    /**
     * Draw 3 labels:
     * 1. "Congratulations!"; center:(300, 150); font_size: 40; bold
     * 2. "Time: 00:00.000"; center:(300, 400); font_size: 32; bold
     * 3. ""Click anywhere to return to home"; center:(300, 600); font_size: 24; bold
     */
    sf::Text congrats("Congratulations!", arial_bold, 40);
    congrats.setFillColor(sf::Color::Black);
    sf::FloatRect congratsRect = congrats.getLocalBounds();
    congrats.setPosition(300 - congratsRect.width / 2, 150 - congratsRect.height);

    sf::Text timeText("Time: " + _format_time(winTime.asSeconds()), arial_bold, 32);
    timeText.setFillColor(sf::Color::Black);
    sf::FloatRect timeTextRect = timeText.getLocalBounds();
    timeText.setPosition(300 - timeTextRect.width / 2, 400 - timeTextRect.height);

    sf::Text returnText("Click anywhere to return to home", arial_bold, 24);
    returnText.setFillColor(sf::Color::Black);
    sf::FloatRect returnTextRect = returnText.getLocalBounds();
    returnText.setPosition(300 - returnTextRect.width / 2, 600 - returnTextRect.height);

    window.draw(congrats);
    window.draw(timeText);
    window.draw(returnText);
}

void xblock::_ui_help(sf::RenderWindow &window) {
    /**
     * Draw the help page
     * 1. title     "Block Transform"; center_x=300; top=50; font_size=32
     * 2. help_text  the help text; center_x=300; top=140; font_size=22
     * 3. example   the example of the game; 100x100; top-left=(110 + 135 * (i % 3), 370 + 135 * (i / 3))
     * */
    sf::Text title("Block Transform", arial_bold, 32);
    title.setFillColor(sf::Color::Black);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setPosition(300 - titleRect.width / 2, 50);

    std::string help_text = "This game requires players to arrange the\n\r"
                            "disordered number blocks in ascending order\n\r"
                            "from left to right and from top to bottom.\n\r"
                            "In each game, the rules for exchanging\n\r"
                            "numbers for each block are determined and\n\r"
                            "players need to explore them themselves.\n\r"
                            "For example, a 3x3 game should be like this:\n\r";
    sf::Text help(help_text, arial, 22);
    help.setFillColor(sf::Color::Black);
    help.setPosition(300 - help.getLocalBounds().width / 2, 140);

    // draw the example
    sf::RectangleShape block[9];
    sf::Text block_text[9];
    for (int i = 0; i < 9; ++i) {
        block[i].setSize(sf::Vector2f(100, 100));
        block[i].setFillColor(sf::Color::Transparent);
        block[i].setOutlineColor(sf::Color::Black);
        block[i].setOutlineThickness(5);
        block[i].setPosition(110 + 135 * (i % 3), 370 + 135 * (i / 3));

        block_text[i].setFont(arial);
        block_text[i].setString(std::to_string(i + 1));
        block_text[i].setCharacterSize(32);
        block_text[i].setFillColor(sf::Color::Black);
        block_text[i].setPosition(160 + 135 * (i % 3) - block_text[i].getLocalBounds().width / 2,
                                  420 + 135 * (i / 3) - block_text[i].getLocalBounds().height);
    }

    window.draw(title);
    window.draw(help);
    for (int i = 0; i < 9; ++i) {
        window.draw(block[i]);
        window.draw(block_text[i]);
    }
}
```

```cpp
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
```

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.28)

# project configuration
project(xblock)
set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)

# set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the SFML library
set(SFML_DIR "libraries/SFML-2.6.1/lib/cmake/SFML")  # TODO: edit this path to the SFMLConfig.cmake file
set(BUILD_SHARED_LIBS TRUE)
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED)

link_libraries(sfml-audio sfml-graphics sfml-window sfml-system)

# add the executable
add_executable(xblock main.cpp
        res/res.rc
        units/topology.cpp
        units/topology.h
        units/ui.h
        units/ui.cpp
        units/event_handling.cpp
        units/event_handling.h
        units/resources.cpp
        units/resources.h
)

# copy the SFML DLLs to the build directory
set(SFML_BIN_DIR ${SFML_DIR}/../../../bin)
file(COPY ${SFML_BIN_DIR}/openal32.dll DESTINATION ${CMAKE_BINARY_DIR})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")  # Debug mode
    file(COPY ${SFML_BIN_DIR}/sfml-graphics-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-window-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-system-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-audio-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
else()                                  # Release mode
    file(COPY ${SFML_BIN_DIR}/sfml-graphics-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-window-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-system-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-audio-2.dll DESTINATION ${CMAKE_BINARY_DIR})
endif()

# copy the resources to the build directory
file(COPY LICENSE DESTINATION ${CMAKE_BINARY_DIR})
file(COPY res/arial.ttf DESTINATION ${CMAKE_BINARY_DIR}/res)
file(COPY res/arialbd.ttf DESTINATION ${CMAKE_BINARY_DIR}/res)
file(COPY res/xblock.png DESTINATION ${CMAKE_BINARY_DIR}/res)
file(COPY res/xnftj.mp3 DESTINATION ${CMAKE_BINARY_DIR}/res)


if(WIN32)
    set_target_properties(xblock PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
```

## 软件运行截图

![0](run/0.png)
![1](run/1.png)
![2](run/2.png)
![3](run/3.png)

## 开源仓库

https://github.com/Jaffe2718/xblock