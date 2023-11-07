#ifndef QUIZ_HPP
#define QUIZ_HPP


#include <vector>
#include "player.hpp"
#include "quizaction.hpp"
#include "clock.hpp"
#include "renderable.hpp"
#include "resources.hpp"
#include "quizstate.hpp"
#include "quizapiclient.hpp"

class Quiz : Renderable {
public:
    ~Quiz();
    void update(const Clock& clock);
    void render();
    QuizState* getState();

    class Builder {
    public:
        Builder& resources(Resources* resources);
        Builder& action(QuizAction* action);
        Builder& player(Player* player);
        Quiz* build();
    private:
        std::vector<QuizAction*> _actions;
        std::vector<Player*> _players;
        Resources* _resources;
    };
    static Builder builder();

private:
    Quiz(QuizState* state, QuizAPIClient* client);

    QuizState* _state;
    Resources* _resources;
    QuizAPIClient* _client;
};

#endif // QUIZ_HPP
