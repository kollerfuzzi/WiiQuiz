#include "qascoreboard.hpp"

#include <cmath>

QAScoreboard::QAScoreboard() {

}

QAScoreboard::~QAScoreboard(){
    delete _playerText;
    delete _points;
    delete _title;
}

void QAScoreboard::init() {
    _state->sortPlayersByScore();
    std::vector<Player*> players = _state->getPlayers();

    std::string playerScores;
    std::string points;

    for (size_t i = 0; i < players.size(); ++i) {
        playerScores += std::to_string(i + 1);
        playerScores += ". ";
        playerScores += players[i]->getName();
        playerScores += "\n";
        points += "| ";
        points += std::to_string(players[i]->getPoints());
        points += " pts.\n";
    }

    _title = TextBox::builder()
        .text("LEADERBOARD")
        .color(RGBA(150, 150, 255, 255))
        .font(_resources->get(Font::C64FONT))
        .fontSize(40)
        .marginTop(40)
        .animationSpeed(50)
        .build();

    _playerText = TextBox::builder()
        .text(playerScores)
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->get(Font::C64FONT))
        .fontSize(20)
        .marginTop(160)
        .animationSpeed(50)
        .build();
    _points = TextBox::builder()
        .text(points)
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->get(Font::C64FONT))
        .fontSize(20)
        .marginTop(160)
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
    _title->update(clock);
    _bgAnimation += 0.04f;
}

void QAScoreboard::render() {
    GRRLIB_DrawImg((int)(-200 + tan(sin(_bgAnimation)/16) * 200),
                   0, _resources->get(Texture::SCOREBOARD_BG), 0, 1, 1.5,
                   RGBA(255, 255, 255, 255));
    _playerText->render();
    _points->render();
    _title->render();
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
