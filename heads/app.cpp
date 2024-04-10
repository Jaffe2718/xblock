#pragma once
#include <QMouseEvent>
#include <iostream>

#include "app.hpp"
#include "game_ui.hpp"

GameWindow::GameWindow() {
    ui_status = HOME;
    timer = new QTimer(this);
    timer->setObjectName("timer");
    // set start as current time
    start = new QTime();
    start->setHMS(0, 0, 0, 0);
    // connect timer to updateTimer
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTimer);
    timer->start(100);
    this->setFixedSize(600, 800);
}

void GameWindow::mousePressEvent(QMouseEvent *event) {
    // get mouse position
    int mouseX, mouseY;
    mouseX = event->pos().x();
    mouseY = event->pos().y();
    switch (this->ui_status) {
        case HOME: {
            handleHome(mouseX, mouseY);
            break;
        }
        case THREE: {
            handle3x3(mouseX, mouseY);
            break;
        }
        case FOUR: {
            handle4x4(mouseX, mouseY);
            break;
        }
        case FIVE: {
            handle5x5(mouseX, mouseY);
            break;
        }
        case WIN: {
            handleWin(mouseX, mouseY);
            break;
        }
        case HELP: {
            handleHelp(mouseX, mouseY);
            break;
        }
        default: {   // invalid status
            throw std::runtime_error("Invalid status");
        }
    }
}

void GameWindow::handleHome(int mouseX, int mouseY) {
    if (mouseX >=100 && mouseX <= 500) {   // 3x3 4x4 5x5 Quit
        if (mouseY >= 200 && mouseY <= 300) {   // 3x3
            this->data = gen_data(9);     // init data 3x3=9
            this->rule = gen_rule(9);     // init rule 3x3=9
            *this->start = QTime::currentTime();
            this->ui_status = THREE;
            ui_3x3(*this, this->data);
        } else if (mouseY >= 350 && mouseY <= 450) {   // 4x4
            this->data = gen_data(16);       // init data 4x4=16
            this->rule = gen_rule(16);       // init rule 4x4=16
            *this->start = QTime::currentTime();
            this->ui_status = FOUR;
            ui_4x4(*this, this->data);
        } else if (mouseY >= 500 && mouseY <= 600) {   // 5x5
            this->data = gen_data(25);    // init data 5x5=25
            this->rule = gen_rule(25);    // init rule 5x5=25
            *this->start = QTime::currentTime();
            this->ui_status = FIVE;
            ui_5x5(*this, this->data);
        } else if (mouseY >= 650 && mouseY <= 750) {   // Quit
            exit(0);
        }
    } else if (mouseX >= 500 && mouseX <= 570 && mouseY >= 80 && mouseY <= 150) {   // Help
        this->ui_status = HELP;
        ui_help(*this);
    }
}

void GameWindow::handle3x3(int mouseX, int mouseY) {
    if (mouseY >= 70 && mouseY <= 150) {
        if (mouseX >= 60 && mouseX <= 180) {          // return to home
            this->ui_status = HOME;
            return ui_home(*this);
        } else if (mouseX >= 420 && mouseX <= 540) {  // reset game
            this->data = gen_data(9);
            this->rule = gen_rule(9);
            *this->start = QTime::currentTime();
            return ui_3x3(*this, this->data);

        }
    } else {                                          // click on the block
        for (int i = 0; i < 9; i++) {
            if (mouseX >= 60 + (i % 3) * 180 && mouseX <= 180 + (i % 3) * 180 &&
                mouseY >= 240 + (i / 3) * 180 && mouseY <= 360 + (i / 3) * 180) {
                transform(this->data, this->rule, i);
                ui_3x3(*this, this->data);
                break;
            }
        }
    }
    if (check_win(this->data)) {
        this->ui_status = WIN;
        double delta = (QTime::currentTime().msecsSinceStartOfDay() - this->start->msecsSinceStartOfDay()) / 1000.0;
        return ui_win(*this, delta);
    }
}

void GameWindow::handle4x4(int mouseX, int mouseY) {
    if (mouseY >= 70 && mouseY <= 150) {
        if (mouseX >= 60 && mouseX <= 180) {          // return to home
            this->ui_status = HOME;
            return ui_home(*this);
        } else if (mouseX >= 420 && mouseX <= 540) {  // reset game
            this->data = gen_data(16);
            this->rule = gen_rule(16);
            *this->start = QTime::currentTime();
            return ui_4x4(*this, this->data);
        }
    } else {                                          // click on the block
        for (int i = 0; i < 16; i++) {
            if (mouseX >= 55 + (i % 4) * 130 && mouseX <= 155 + (i % 4) * 130 &&
                mouseY >= 240 + (i / 4) * 130 && mouseY <= 340 + (i / 4) * 130) {
                transform(this->data, this->rule, i);
                ui_4x4(*this, this->data);
                break;
            }
        }
    }
    if (check_win(this->data)) {
        this->ui_status = WIN;
        double delta = (QTime::currentTime().msecsSinceStartOfDay() - this->start->msecsSinceStartOfDay()) / 1000.0;
        return ui_win(*this, delta);
    }
}

void GameWindow::handle5x5(int mouseX, int mouseY) {
    if (mouseY >= 70 && mouseY <= 150) {
        if (mouseX >= 60 && mouseX <= 180) {          // return to home
            this->ui_status = HOME;
            return ui_home(*this);
        } else if (mouseX >= 420 && mouseX <= 540) {  // reset game
            this->data = gen_data(25);
            this->rule = gen_rule(25);
            *this->start = QTime::currentTime();
            return ui_5x5(*this, this->data);

        }
    } else {                                          // click on the block
        for (int i = 0; i < 25; i++) {
            if (mouseX >= 60 + (i % 5) * 100 && mouseX <= 140 + (i % 5) * 100 &&
                mouseY >= 240 + (i / 5) * 100 && mouseY <= 320 + (i / 5) * 100) {
                transform(this->data, this->rule, i);
                ui_5x5(*this, this->data);
                break;
            }
        }
    }
    if (check_win(this->data)) {
        this->ui_status = WIN;
        double delta = (QTime::currentTime().msecsSinceStartOfDay() - this->start->msecsSinceStartOfDay()) / 1000.0;
        return ui_win(*this, delta);
    }
}

void GameWindow::handleWin(int mouseX, int mouseY) {
    this->ui_status = HOME;    // return to home
    ui_home(*this);
}

void GameWindow::handleHelp(int mouseX, int mouseY) {
    this->ui_status = HOME;    // return to home
    ui_home(*this);
}

void GameWindow::updateTimer() {
    if (this->ui_status == THREE || this->ui_status == FOUR || this->ui_status == FIVE) {
        double delta = QTime::currentTime().msecsSinceStartOfDay() - this->start->msecsSinceStartOfDay();
        // turn to string like "05:05", fill with 0
        std::string min = std::to_string((int) delta / 60000);
        std::string sec = std::to_string((int) delta / 1000 % 60);
        if (min.length() == 1) {
            min = "0" + min;
        }
        if (sec.length() == 1) {
            sec = "0" + sec;
        }
        std::string time = min + ":" + sec;
        ui_time(*this, time);
    }
}

