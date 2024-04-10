#pragma once
#ifndef GAME_UI_HPP
#define GAME_UI_HPP

#include <QMainWindow>
#include <QLabel>
#include "game_ui.hpp"


void ui_home(QMainWindow &window) {
    /**
     * Draw the home page
     * There are 6 labels:
     * 1. title     "Block Transform"; center:(300,60); font_size: 40; bold
     * 2. 3x3       "3x3"; rect_size: 400x100; center:(300, 200); font_size: 28; border: 5px solid black
     * 3. 4x4       "4x4"; rect_size: 400x100; center:(300, 350); font_size: 28; border: 5px solid black
     * 4. 5x5       "5x5"; rect_size: 400x100; center:(300, 500); font_size: 28; border: 5px solid black
     * 5. Help      "?"; center:(535, 80); font_size: 24; rect_size: 70x70; border: 5px solid black
     * 6. Quit      "Quit"; rect_size: 400x100; center:(300, 650); font_size: 24; border: 5px solid black
    * */
    // clear the window
    qDeleteAll(window.findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
    // set the title
    auto *title = new QLabel("Block Transform", &window);
    title->resize(600, 60);       // 600x60
    title->move(0, 80);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 40px; font-weight: bold");
    title->show();
    // draw the buttons ?
    auto *help = new QLabel("?", &window);
    help->resize(70, 70);
    help->move(500, 80);
    help->setAlignment(Qt::AlignCenter);
    help->setStyleSheet("font-size: 24px; border: 5px solid black; font-weight: bold");
    help->show();
    // draw the buttons 3x3 4x4 5x5 Quit
    auto *three = new QLabel("3x3", &window);
    three->resize(400, 100);
    three->move(100, 200);
    three->setAlignment(Qt::AlignCenter);
    three->setStyleSheet("font-size: 28px; border: 5px solid black; font-weight: bold");
    three->show();
    auto *four = new QLabel("4x4", &window);
    four->resize(400, 100);
    four->move(100, 350);
    four->setAlignment(Qt::AlignCenter);
    four->setStyleSheet("font-size: 28px; border: 5px solid black; font-weight: bold");
    four->show();
    auto *five = new QLabel("5x5", &window);
    five->resize(400, 100);
    five->move(100, 500);
    five->setAlignment(Qt::AlignCenter);
    five->setStyleSheet("font-size: 28px; border: 5px solid black; font-weight: bold");
    five->show();
    auto *quit = new QLabel("Quit", &window);
    quit->resize(400, 100);
    quit->move(100, 650);
    quit->setAlignment(Qt::AlignCenter);
    quit->setStyleSheet("font-size: 28px; border: 5px solid black; font-weight: bold");
    quit->show();
}

void _ui_menu(QMainWindow &window) {
    // clear the window except the time label
    foreach (auto *widget, window.findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
        if (widget->objectName() != "time_label") {
            delete widget;
        }
    }
    // draw the main frame
    auto *main_frame = new QLabel(&window);
    main_frame->resize(520, 120);
    main_frame->move(40, 50);
    main_frame->setStyleSheet("border: 5px solid black");
    main_frame->show();
    // draw the buttons Home Reset
    auto *home = new QLabel("Home", &window);
    home->resize(120, 80);
    home->move(60, 70);
    home->setAlignment(Qt::AlignCenter);
    home->setStyleSheet("font-size: 24px; border: 5px solid black; font-weight: bold");
    home->show();
    auto *_reset = new QLabel("Reset", &window);
    _reset->resize(120, 80);
    _reset->move(420, 70);
    _reset->setAlignment(Qt::AlignCenter);
    _reset->setStyleSheet("font-size: 24px; border: 5px solid black; font-weight: bold");
    _reset->show();
}

void ui_time(QMainWindow &window, const std::string& tick) {

    // check if the time label exists
    auto *time_lb = window.findChild<QLabel*>("time_label");
    if (!time_lb) {
        time_lb = new QLabel(QString(tick.c_str()), &window);
    } else {
        time_lb->setText(QString(tick.c_str()));
    }
    time_lb->setObjectName("time_label");
    time_lb->resize(120, 80);
    time_lb->move(240, 70);
    time_lb->setAlignment(Qt::AlignCenter);
    time_lb->setStyleSheet("font-size: 24px; font-weight: bold");
    time_lb->show();
}

void ui_3x3(QMainWindow &window, std::vector<int> &data) {
    // draw the menu bar
    _ui_menu(window);
    // draw the 3x3 grid
    auto grid = new QLabel*[9];
    for (int i = 0; i < 9; ++i) {
        grid[i] = new QLabel(QString::number(data[i]), &window);
        grid[i]->resize(120, 120);
        grid[i]->move(60 + (i % 3) * 180, 240 + (i / 3) * 180);
        grid[i]->setAlignment(Qt::AlignCenter);
        grid[i]->setStyleSheet("font-size: 32px; border: 5px solid black; font-weight: bold");
        grid[i]->show();
    }
}

void ui_4x4(QMainWindow &window, std::vector<int> &data) {
    // draw the menu bar
    _ui_menu(window);
    // draw the 4x4 grid
    auto grid = new QLabel*[16];
    for (int i = 0; i < 16; ++i) {
        grid[i] = new QLabel(QString::number(data[i]), &window);
        grid[i]->resize(100, 100);
        grid[i]->move(55 + (i % 4) * 130, 240 + (i / 4) * 130);
        grid[i]->setAlignment(Qt::AlignCenter);
        grid[i]->setStyleSheet("font-size: 32px; border: 5px solid black; font-weight: bold");
        grid[i]->show();
    }
}

void ui_5x5(QMainWindow &window, std::vector<int> &data) {
    // draw the menu bar
    _ui_menu(window);
    // draw the 5x5 grid
    auto grid = new QLabel*[25];
    for (int i = 0; i < 25; ++i) {
        grid[i] = new QLabel(QString::number(data[i]), &window);
        grid[i]->resize(80, 80);
        grid[i]->move(60 + (i % 5) * 100, 240 + (i / 5) * 100);
        grid[i]->setAlignment(Qt::AlignCenter);
        grid[i]->setStyleSheet("font-size: 32px; border: 5px solid black; font-weight: bold");
        grid[i]->show();
    }
}

void ui_win(QMainWindow &window, double tick) {
    // clear the window
    qDeleteAll(window.findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
    // draw the congratulation text
    auto *congrat = new QLabel("Congratulations!", &window);
    congrat->resize(600, 80);
    congrat->move(0, 100);
    congrat->setAlignment(Qt::AlignCenter);
    congrat->setStyleSheet("font-size: 40px; font-weight: bold");
    congrat->show();
    // draw the time text
    auto *time_lb = new QLabel(QString("Time: %2s").arg(tick), &window);
    time_lb->resize(600, 60);
    time_lb->move(0, 375);
    time_lb->setAlignment(Qt::AlignCenter);
    time_lb->setStyleSheet("font-size: 32px; font-weight: bold");
    time_lb->show();
    // draw the "click anywhere to return to home" text
    auto *return_lb = new QLabel("Click anywhere to return to home", &window);
    return_lb->resize(600, 60);
    return_lb->move(0, 510);
    return_lb->setAlignment(Qt::AlignCenter);
    return_lb->setStyleSheet("font-size: 24px; font-weight: bold");
    return_lb->show();
}

void ui_help(QMainWindow &window) {
    // clear the window
    qDeleteAll(window.findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
    // set the title
    auto * title = new QLabel("Block Transform Help", &window);
    title->resize(600, 60);       // 600x60
    title->move(0, 50);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 32px; font-weight: bold");
    title->show();                      // ensure the title is shown
    // draw the help text
    std::string help_text = "This game requires players to arrange the\n\r"
                            "disordered number blocks in ascending order\n\r"
                            "from left to right and from top to bottom.\n\r"
                            "In each game, the rules for exchanging\n\r"
                            "numbers for each block are determined and\n\r"
                            "players need to explore them themselves.\n\r"
                            "For example, a 3x3 game should be like this:\n\r";
    auto * help = new QLabel(QString::fromStdString(help_text), &window);
    help->resize(600, 250);
    help->move(0, 130);
    help->setAlignment(Qt::AlignCenter);
    help->setWordWrap(true);
    help->setStyleSheet("font-size: 22px; font-weight: bold");
    help->show();
    // draw the example, each number is a label
    // 1 2 3
    // 4 5 6
    // 7 8 9
    auto example = new QLabel*[9];
    for (int i = 0; i < 9; i++) {
        example[i] = new QLabel(QString::number(i + 1), &window);
        example[i]->resize(100, 100);
        example[i]->move(115 + 135 * (i % 3), 380 + 135 * (i / 3));
        example[i]->setAlignment(Qt::AlignCenter);
        example[i]->setStyleSheet("font-size: 32px; border: 5px solid black; font-weight: bold");
        example[i]->show();
    }
}

#endif // GAME_UI_HPP