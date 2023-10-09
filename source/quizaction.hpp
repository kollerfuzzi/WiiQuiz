#ifndef QUIZACTION_HPP
#define QUIZACTION_HPP

#include <vector>

#include "renderable.hpp"
#include "resources.hpp"
#include "player.hpp"

class QuizAction {
public:
    virtual ~QuizAction() = 0;
    virtual void update(const Clock& clock) = 0;
    virtual void render() = 0;
    virtual bool isDone() = 0;
    void setResources(Resources* resources);
    void setPlayers(std::vector<Player*> players);
protected:
    Resources* _resources;
    std::vector<Player*> _players;
};

#endif // QUIZACTION_HPP
