#include "qascoreboard.hpp"

#include <cmath>

QAScoreboard::QAScoreboard() {

}

QAScoreboard::~QAScoreboard(){
    _cleanup();
}

void QAScoreboard::_init() {
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
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(40)
        .marginTop(40)
        .animationSpeed(50)
        .build();

    _playerText = TextBox::builder()
        .text(playerScores)
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(20)
        .marginTop(160)
        .animationSpeed(50)
        .build();
    _points = TextBox::builder()
        .text(points)
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(20)
        .marginTop(160)
        .marginLeft(400)
        .animationSpeed(50)
        .build();
    _confirm = Confirm::builder()
        .resources(_resources)
        .build();

    _initialized = true;
}

void QAScoreboard::update(Clock &clock) {
    if (!_initialized) {
        _init();
    }
    _playerText->update(clock);
    _points->update(clock);
    _title->update(clock);
    _confirm->update(clock);
    _isDone = _confirm->isConfirmed();
    _bgAnimation += 0.04f;
}

void QAScoreboard::render() {
    GRRLIB_DrawImg((int)(-200 + tan(sin(_bgAnimation)/16) * 200),
                   0, _resources->getTexture(Texture::SCOREBOARD_BG), 0, 1, 1.5,
                   RGBA(255, 255, 255, 255));
    _playerText->render();
    _points->render();
    _title->render();
    _confirm->render();
}

bool QAScoreboard::isDone() {
    return _isDone;
}

void QAScoreboard::reset() {
    _cleanup();
}

QAScoreboard::Builder QAScoreboard::builder() {
    return QAScoreboard::Builder();
}

void QAScoreboard::_cleanup() {
    if (_title != nullptr) {
        delete _title;
        _title = nullptr;
    }
    if (_playerText != nullptr) {
        delete _playerText;
        _playerText = nullptr;
    }
    if (_points != nullptr) {
        delete _points;
        _points = nullptr;
    }
    if (_confirm != nullptr) {
        delete _confirm;
        _confirm = nullptr;
    }

    _initialized = false;
    _isDone = false;
    _bgAnimation = 0.0f;
}

QAScoreboard *QAScoreboard::Builder::build() {
    return new QAScoreboard();
}
