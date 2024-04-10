#include <QApplication>
#include <QDir>
#include <QMouseEvent>
#include <QtMultimedia/QAudioDevice>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlayer>

#include "heads/app.hpp"
#include "heads/game_ui.hpp"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameWindow window;
    window.resize(600, 800);
    window.setWindowTitle("Block Transform");
    ui_home(window);
    auto *audioOutput = new QAudioOutput(&window);
    audioOutput->setVolume(1.0);
    QDir dir((QCoreApplication::applicationDirPath()));       // get the path of the executable
    QString audioPath = dir.filePath("res/xnftj.mp3");    // complete path
    QMediaPlayer player;
    player.stop();
    player.setAudioOutput(audioOutput);
    player.setSource(QUrl::fromLocalFile(audioPath));
    player.setLoops(-1);
    player.play();

    window.show();
    return QApplication::exec();
}
