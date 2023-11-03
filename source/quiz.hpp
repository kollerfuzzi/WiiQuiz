#ifndef QUIZ_HPP
#define QUIZ_HPP


#include <vector>
#include "player.hpp"
#include "quizaction.hpp"
#include "clock.hpp"
#include "renderable.hpp"
#include "resources.hpp"


class Quiz : Renderable {
public:
    ~Quiz();
    void update(const Clock& clock);
    void render();
    std::vector<Player*> getPlayers();

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
    Quiz(Resources* resources, std::vector<QuizAction*> actions,
         std::vector<Player*> players);
    std::vector<QuizAction*> _actions;
    std::vector<Player*> _players;
    size_t _currentAction = 0;
    Resources* _resources;
};

#endif // QUIZ_HPP
