#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include "renderable.hpp"
#include "textbox.hpp"
#include "resources.hpp"
#include "wiimote.hpp"
#include "swinginglights.hpp"

#define ITEM_MARGIN_LEFT 200
#define ITEM_MARGIN_TOP 100
#define ITEM_SPACING 50


class MenuItem  {
public:
    MenuItem(std::string text, std::vector<MenuItem*> child, MenuItem* parent,
             Renderable* renderable, bool quit);
    ~MenuItem();

    std::string getText();
    std::vector<MenuItem*> getChildren();
    void setParent(MenuItem* parent);
    MenuItem* getParent();
    void setTextBox(TextBox* textBox);
    TextBox* getTextBox();
    Renderable* getRenderable();
    bool isQuit();

    class Builder {
    public:
        Builder& text(std::string text);
        Builder& child(MenuItem* child);
        Builder& parent(MenuItem* parent);
        Builder& renderable(Renderable* renderable);
        Builder& quit(bool quit);
        MenuItem* build();
    private:
        std::string _text;
        std::vector<MenuItem*> _children;
        MenuItem* _parent = nullptr;
        Renderable* _renderable = nullptr;
        bool _quit = false;
    };
    static Builder builder();

private:
    std::string _text;
    TextBox* _textBox = nullptr;
    std::vector<MenuItem*> _children;
    MenuItem* _parent = nullptr;
    Renderable* _renderable = nullptr;
    bool _quit;
};

class Menu : public Renderable {
public:
    Menu(Resources* resources, MenuItem* root);
    ~Menu();
    void update(Clock& clock);
    void render();
    bool isDone();
private:
    void _updateSubMenus(Clock& clock);
    void _updateSelection();
    void _select(MenuItem* menuItem, Clock& clock);
    void _back();
    MenuItem* _root = nullptr;
    MenuItem* _currentSubMenu = nullptr;
    MenuItem* _currentSelected = nullptr;
    Resources* _resources = nullptr;
    SwingingLights* _swingingLights = nullptr;
    bool _isDone;
};

#endif // MENU_HPP
