#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <cstdint>

class Player {
public:
    class Builder {
    public:
        Builder& name(std::string name);
        Builder& points(int32_t points);
        Player* build();
    private:
        std::string _name;
        int32_t _points = 0;
    };

    static Builder builder();
    std::string getName();
    int32_t getPoints();
    void addPoints(int32_t points);
    std::string to_str();
private:
    Player(std::string name, int32_t points);
    std::string _name;
    int32_t _points;
};

#endif // PLAYER_HPP
