#include "player.hpp"
#include "tinyuuidv4.hpp"

Player::Player(std::string id, std::string name, int32_t points) {
    _id = id;
    _name = name;
    _points = points;
}

Player::Builder Player::builder() {
    return Player::Builder();
}

std::string Player::getId() {
    return _id;
}

std::string Player::getName() {
    return _name;
}

int32_t Player::getPoints() {
    return _points;
}

void Player::addPoints(int32_t points) {
    _points += points;
}

std::string Player::to_str() {
    std::string string_repr("Player{name=");
    string_repr += _name;
    string_repr += ";points=";
    string_repr += std::to_string(_points);
    string_repr += "}";
    return string_repr;
}

Player::Builder::Builder() {
    _id = TinyUuidV4::generate();
}

Player::Builder& Player::Builder::id(std::string id) {
    _id = id;
    return *this;
}

Player::Builder& Player::Builder::name(std::string name)
{
    _name = name;
    return *this;
}

Player::Builder& Player::Builder::points(int32_t points) {
    _points = points;
    return *this;
}

Player* Player::Builder::build() {
    return new Player(_id, _name, _points);
}
