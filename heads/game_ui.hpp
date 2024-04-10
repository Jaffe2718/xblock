#include <vector>             // vector

#include <QMainWindow>



void ui_home(QMainWindow &window);

void _ui_menu(QMainWindow &window);

void ui_time(QMainWindow &window, const std::string& tick);

void ui_3x3(QMainWindow &window, std::vector<int> &data);

void ui_4x4(QMainWindow &window, std::vector<int> &data);

void ui_5x5(QMainWindow &window, std::vector<int> &data);

void ui_win(QMainWindow &window, double tick);

void ui_help(QMainWindow &window);