#include "player.hpp"


Player::Player(std::string name) {
    _name = name;
}

Player::Builder Player::builder() {
    return Player::Builder();
}

std::string Player::getName() {
    return _name;
}

int Player::getPoints() {
    return _points;
}

Player::Builder& Player::Builder::name(std::string name) {
    _name = name;
    return *this;
}

Player* Player::Builder::build() {
    return new Player(_name);
}
