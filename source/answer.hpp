#ifndef ANSWER_HPP
#define ANSWER_HPP

#include <string>
#include <vector>

#include "player.hpp"

class Answer {
public:
    Player* getPlayer();
    std::vector<std::string> getAnswers();
    bool isApproved();
    class Builder {
    public:
        Builder& player(Player* player);
        Builder& answer(std::string answer);
        Builder& approved(bool approved);
        Answer build();
    private:
        Player* _player;
        std::vector<std::string> _answers;
        bool _approved;
    };
    static Builder builder();
private:
    Answer(Player* player, std::vector<std::string> answers, bool approved);
    Player* _player;
    std::vector<std::string> _answers;
    bool _approved;
};

#endif // ANSWER_HPP
