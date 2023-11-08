#include "qastart.hpp"


QAStart::QAStart() {

}

QAStart::~QAStart() {
    delete _welcomeText;
    delete _playerText;
    delete _startConfirm;
}

void QAStart::init() {
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
        .font(_resources->get(Font::C64FONT))
        .fontSize(20)
        .marginTop(50)
        .marginLeft(50)
        .marginRight(50)
        .animationSpeed(50)
        .build();
    _playerText = TextBox::builder()
        .text("")
        .color(RGBA(180, 100, 255, 255))
        .font(_resources->get(Font::C64FONT))
        .fontSize(15)
        .marginTop(200)
        .marginLeft(75)
        .marginRight(75)
        .build();
    _startConfirm = Confirm::builder()
        .resources(_resources)
        .enabled(false)
        .build();

    _initialized = true;
}

void QAStart::update(const Clock &clock) {
    init();

    _lightx += 0.05f;
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
}

void QAStart::render() {

    GRRLIB_Camera3dSettings(0.0f,0.0f,3.0f, 0,1,0, 0,0,0);

    GRRLIB_SetLightAmbient(0x404040FF);

    GRRLIB_SetLightSpot(1, (guVector){(f32) (sin(_lightx)*2.5f), 0.8f, 0 },
                        (guVector){(f32) (sin(_lightx)*2.5f), 0.0f, 0.0f },
                        -4.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0x0000FFFF);
    GRRLIB_SetLightSpot(2, (guVector){(f32) (-sin(_lightx)*2.5f), 0.8f, 0 },
                        (guVector){(f32) (-sin(_lightx)*2.5f), 0.0f, 0.0f },
                        -4.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0xFF0000FF);

    GRRLIB_3dMode(0.1,1000,45,0,1);
    GRRLIB_ObjectView(0,-0.8 ,0 ,-90 ,0 ,0 ,1 ,1 ,1 );
    GRRLIB_DrawTessPanel(6.2f,0.17f,3.7f,0.1f,0,0xFFFFFFFF);

    GRRLIB_2dMode();
    _welcomeText->render();
    _playerText->render();
    _startConfirm->render();
}

bool QAStart::isDone() {
    return _started;
}

QAStart::Builder QAStart::builder() {
    return QAStart::Builder();
}

QAStart *QAStart::Builder::build() {
    return new QAStart();
}
