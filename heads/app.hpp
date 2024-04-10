#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>             // vector
#include <unordered_map>      // hash map

#include <QMainWindow>
#include <QTime>
#include <QTimer>

#include "graph.hpp"


enum UI_Status {
    HOME,
    THREE,
    FOUR,
    FIVE,
    WIN,
    HELP
};

class GameWindow : public QMainWindow {   // TODO deprecated, use QMainWindow instead
    Q_OBJECT
public:
    UI_Status ui_status;                 // current ui status
    std::vector<int> data;               // data of the game
    std::unordered_map<int, int> rule;   // position of the game
    QTime *start;                        // game time
    QTimer *timer;                       // timer of the game
    GameWindow();

public
    slots:
            void updateTimer();

private:
    void handleHome(int mouseX, int mouseY);

    void handle3x3(int mouseX, int mouseY);

    void handle4x4(int mouseX, int mouseY);

    void handle5x5(int mouseX, int mouseY);

    void handleWin(int mouseX, int mouseY);

    void handleHelp(int mouseX, int mouseY);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H