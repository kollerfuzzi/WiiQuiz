#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <cstdint>

class Player {
public:
    class Builder {
    public:
        Builder& name(std::string name);
        Player* build();
    private:
        std::string _name;
    };

    static Builder builder();
    std::string getName();
    int getPoints();
private:
    Player(std::string name);
    std::string _name;
    int32_t _points = 0;
};

#endif // PLAYER_HPP
