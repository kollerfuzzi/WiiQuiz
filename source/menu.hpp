#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include "renderable.hpp"
#include "textbox.hpp"
#include "resources.hpp"
#include "wiimote.hpp"

#define ITEM_MARGIN_LEFT 200
#define ITEM_MARGIN_TOP 100
#define ITEM_SPACING 50


class MenuItem  {
public:
    MenuItem(std::string text, std::vector<MenuItem*> child, MenuItem* parent);
    ~MenuItem();

    std::string getText();
    std::vector<MenuItem*> getChildren();
    void setParent(MenuItem* parent);
    MenuItem* getParent();
    void setTextBox(TextBox* textBox);
    TextBox* getTextBox();

    class Builder {
    public:
        Builder& text(std::string text);
        Builder& child(MenuItem* child);
        Builder& parent(MenuItem* parent);
        MenuItem* build();
    private:
        std::string _text;
        std::vector<MenuItem*> _children;
        MenuItem* _parent = nullptr;
    };
    static Builder builder();

private:
    std::string _text;
    TextBox* _textBox = nullptr;
    std::vector<MenuItem*> _children;
    MenuItem* _parent = nullptr;
    void(*action)();
};

class Menu : public Renderable {
public:
    Menu(Resources* resources, MenuItem* root);
    ~Menu();
    void update(const Clock& clock);
    void render();
private:
    void _updateSubMenus(const Clock& clock);
    void _updateSelection();
    void _select(MenuItem* menuItem);
    void _back();
    MenuItem* _root = nullptr;
    MenuItem* _currentSubMenu = nullptr;
    MenuItem* _currentSelected = nullptr;
    Resources* _resources = nullptr;
};

#endif // MENU_HPP
