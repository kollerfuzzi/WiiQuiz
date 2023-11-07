#ifndef ANSWER_HPP
#define ANSWER_HPP

#include <string>

#include "player.hpp"

class Answer {
public:
    Player* getPlayer();
    std::string getAnswer();
    class Builder {
    public:
        Builder& player(Player* player);
        Builder& answer(std::string answer);
        Answer build();
    private:
        Player* _player;
        std::string _answer;
    };
    static Builder builder();
private:
    Answer(Player* player, std::string answer);
    Player* _player;
    std::string _answer;
};

#endif // ANSWER_HPP
