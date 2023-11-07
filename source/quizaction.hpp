#ifndef QUIZACTION_HPP
#define QUIZACTION_HPP

#include <vector>

#include "renderable.hpp"
#include "resources.hpp"
#include "player.hpp"
#include "quizstate.hpp"
#include "quizapiclient.hpp"

class QuizState;
class QuizAPIClient;

class QuizAction {
public:
    virtual ~QuizAction() = 0;
    virtual void update(const Clock& clock) = 0;
    virtual void render() = 0;
    virtual bool isDone() = 0;
    void setResources(Resources* resources);
    void setState(QuizState* state);
    void setClient(QuizAPIClient* state);
protected:
    Resources* _resources;
    QuizState* _state;
    QuizAPIClient* _client;
};

#endif // QUIZACTION_HPP
