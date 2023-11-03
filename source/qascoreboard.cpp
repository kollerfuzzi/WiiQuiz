#include "qascoreboard.hpp"

QAScoreboard::QAScoreboard() {

}

QAScoreboard::~QAScoreboard(){

}

bool pointSort(Player* p1, Player* p2) {
    return p1->getPoints() > p2->getPoints();
}

void QAScoreboard::init() {
    std::sort(_players.begin(), _players.end(), pointSort);
    std::string playerScores;
    std::string points;

    for (size_t i = 0; i < _players.size(); ++i) {
        playerScores += std::to_string(i + 1);
        playerScores += ". ";
        playerScores += _players[i]->getName();
        playerScores += "\n";
        points += "| ";
        points += std::to_string(_players[i]->getPoints());
        points += " pts.\n";
    }

    _playerText = TextBox::builder()
        .text(playerScores)
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->get(Font::C64FONT))
        .fontSize(20)
        .marginTop(130)
        .animationSpeed(50)
        .build();
    _points = TextBox::builder()
        .text(points)
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->get(Font::C64FONT))
        .fontSize(20)
        .marginTop(130)
        .marginLeft(400)
        .animationSpeed(50)
        .build();
    _initialized = true;
}

void QAScoreboard::update(const Clock &clock) {
    if (!_initialized) {
        init();
    }
    _playerText->update(clock);
    _points->update(clock);
}

void QAScoreboard::render() {
    GRRLIB_DrawImg(0, 0, _resources->get(Texture::SCOREBOARD_BG), 0, 1, 1.5,
                   RGBA(255, 255, 255, 255));
    _playerText->render();
    _points->render();
}

bool QAScoreboard::isDone() {
    return false;
}

QAScoreboard::Builder QAScoreboard::builder() {
    return QAScoreboard::Builder();
}

QAScoreboard *QAScoreboard::Builder::build() {
    return new QAScoreboard();
}
