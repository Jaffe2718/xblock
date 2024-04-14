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
