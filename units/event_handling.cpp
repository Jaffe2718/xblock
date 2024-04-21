//
// Created by lfkex on 2024/4/11.
//

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