#include "qalobby.hpp"


QALobby::QALobby() {

}

QALobby::~QALobby() {
    _cleanup();
}

void QALobby::init() {
    if (_initialized) {
        return;
    }
    std::string welcome("Welcome to the quiz!\n");
    welcome += "Connect to \"";
    welcome += _client->getServerAddress();
    welcome += "\"";
    welcome += "\nand enter your name.\n\nLobby:\n";

    _welcomeText = TextBox::builder()
        .text(welcome)
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(20)
        .marginTop(50)
        .marginLeft(50)
        .marginRight(50)
        .animationSpeed(50)
        .build();
    _playerText = TextBox::builder()
        .text("")
        .color(RGBA(180, 100, 255, 255))
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(15)
        .marginTop(200)
        .marginLeft(75)
        .marginRight(75)
        .build();
    _startConfirm = Confirm::builder()
        .resources(_resources)
        .enabled(false)
        .build();

    _swingingLights = new SwingingLights();

    AudioPlayer::play(Audio::GETTING_READY, _resources);

    _initialized = true;
}

void QALobby::update(Clock &clock) {
    init();

    if (_loadTimer <= 0) {
        _client->loadPlayers();
        std::string players;
        for (Player* pl : _state->getPlayers()) {
            players += "> ";
            players += pl->getName();
            players += "\n";
        }
        if (players.size() == 0) {
            players += "Noone joined yet.";
        }
        _playerText->setText(players);
        _playerText->copyBufferToContent();
        _loadTimer = 120;
    }
    _welcomeText->update(clock);

    _startConfirm->update(clock);
    _startConfirm->setEnabled(!_state->getPlayers().empty());
    _started = _startConfirm->isConfirmed();

    _loadTimer--;
    _swingingLights->update(clock);
}

void QALobby::render() {
    _swingingLights->render();
    _welcomeText->render();
    _playerText->render();
    _startConfirm->render();
}

bool QALobby::isDone() {
    return _started;
}

void QALobby::reset() {
    _cleanup();
}

QALobby::Builder QALobby::builder() {
    return QALobby::Builder();
}

void QALobby::_cleanup() {
    if (_welcomeText != nullptr) {
        delete _welcomeText;
        _welcomeText = nullptr;
    }
    if (_playerText != nullptr) {
        delete _playerText;
        _playerText = nullptr;
    }
    if (_startConfirm != nullptr) {
        delete _startConfirm;
        _startConfirm = nullptr;
    }
    if (_swingingLights != nullptr) {
        delete _swingingLights;
        _swingingLights = nullptr;
    }
    _initialized = false;
    _started = false;
    _loadTimer = 0;
}

QALobby *QALobby::Builder::build() {
    return new QALobby();
}
