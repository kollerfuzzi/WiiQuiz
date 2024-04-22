#include "menu.hpp"
#include "audioplayer.hpp"
MenuItem::MenuItem(std::string text,
                   std::vector<MenuItem*> children,
                   MenuItem* parent,
                   Renderable* renderable,
                   bool quit) {
    _text = text;
    _children = children;
    for (MenuItem* child : _children) {
        child->setParent(this);
    }
    _parent = parent;
    _renderable = renderable;
    _quit = quit;
}

MenuItem::~MenuItem() {
    for (MenuItem* child : _children) {
        delete child;
    }
    if (_textBox != nullptr) {
        delete _textBox;
    }
}

std::string MenuItem::getText() {
    return _text;
}

std::vector<MenuItem*> MenuItem::getChildren() {
    return _children;
}

void MenuItem::setParent(MenuItem* parent) {
    _parent = parent;
}

MenuItem* MenuItem::getParent() {
    return _parent;
}

void MenuItem::setTextBox(TextBox* textBox) {
    _textBox = textBox;
}

TextBox* MenuItem::getTextBox() {
    return _textBox;
}

Renderable* MenuItem::getRenderable() {
    return _renderable;
}

bool MenuItem::isQuit() {
    return _quit;
}

MenuItem::Builder MenuItem::builder() {
    return MenuItem::Builder();
}

Menu::Menu(Resources* resources, MenuItem* root) {
    _resources = resources;
    _root = root;
    _currentSubMenu = _root;
    _swingingLights = new SwingingLights();
}

Menu::~Menu() {
    if (_swingingLights != nullptr) {
        delete _swingingLights;
    }
    delete _root;
}

void Menu::update(Clock& clock) {
    _updateSelection();
    if (WiiMote::buttonPressed(Remote::R1, Button::A)
            && _currentSelected != nullptr) {
        _select(_currentSelected, clock);
    }
    if (WiiMote::buttonPressed(Remote::R1, Button::B)) {
        _back();
    }
    _swingingLights->update(clock);
    _updateSubMenus(clock);
}

void Menu::_updateSubMenus(Clock& clock) {
    for (size_t i = 0; i < _currentSubMenu->getChildren().size(); i++) {
        MenuItem* menuItem = _currentSubMenu->getChildren()[i];
        if (menuItem->getTextBox() == nullptr) {
            menuItem->setTextBox(TextBox::builder()
                                     .text(menuItem->getText())
                                     .font(_resources->get(Font::DEFAULT_FONT))
                                     .fontSize(20)
                                     .marginLeft(ITEM_MARGIN_LEFT + 5)
                                     .marginTop(ITEM_MARGIN_TOP + i * ITEM_SPACING + 5)
                                     .build());

            menuItem->getTextBox()->update(clock);
        }
    }
}

void Menu::_updateSelection() {
    Pointer ptr = WiiMote::getPointerPosition(Remote::R1);
    if (ptr.onScreen && ptr.xPos > ITEM_MARGIN_LEFT && ptr.xPos < ITEM_MARGIN_LEFT + 240) {
        size_t y = (ptr.yPos - ITEM_MARGIN_TOP) / ITEM_SPACING;
        if (y >= 0 && y < _currentSubMenu->getChildren().size()) {
            _currentSelected = _currentSubMenu->getChildren()[y];
        } else {
            _currentSelected = nullptr;
        }
    } else {
        _currentSelected = nullptr;
    }
}

void Menu::render() {
    _swingingLights->render();
    for (size_t i = 0; i < _currentSubMenu->getChildren().size(); i++) {
        MenuItem* menuItem = _currentSubMenu->getChildren()[i];
        int textColor = RGBA(150, 150, 255, 255);
        if (menuItem == _currentSelected) {
            textColor = RGBA(255, 255, 255, 255);
            GRRLIB_DrawImg(ITEM_MARGIN_LEFT - 20, ITEM_MARGIN_TOP + (i * ITEM_SPACING),
                           _resources->get(Texture::MENU_BUTTON), 0, 2.4f, 1,
                           RGBA(255, 255, 255, 255));
        } else {
            GRRLIB_DrawImg(ITEM_MARGIN_LEFT - 10, ITEM_MARGIN_TOP + (i * ITEM_SPACING),
                           _resources->get(Texture::MENU_BUTTON), 0, 2.2f, 1,
                           RGBA(255, 255, 255, 200));
        }
        menuItem->getTextBox()->setColor(textColor);

        menuItem->getTextBox()->render();
    }
}

bool Menu::isDone() {
    return _currentSubMenu->isQuit();
}

void Menu::reset() {
    _currentSubMenu = _root;
}

void Menu::_select(MenuItem* menuItem, Clock& clock) {
    if (menuItem->getRenderable() == nullptr) {
        _currentSubMenu = menuItem;
    } else {
        menuItem->getRenderable()->runUntilDone(clock, _resources->get(Texture::CURSOR));
    }
}

void Menu::_back() {
    if (_currentSubMenu == _root) {
        return;
    }
    _currentSubMenu = _currentSubMenu->getParent();
}

MenuItem::Builder& MenuItem::Builder::text(std::string text) {
    _text = text;
    return *this;
}

MenuItem::Builder& MenuItem::Builder::child(MenuItem* child) {
    _children.push_back(child);
    return *this;
}

MenuItem::Builder& MenuItem::Builder::parent(MenuItem* parent) {
    _parent = parent;
    return *this;
}

MenuItem::Builder& MenuItem::Builder::renderable(Renderable* renderable) {
    _renderable = renderable;
    return *this;
}

MenuItem::Builder& MenuItem::Builder::quit(bool quit) {
    _quit = true;
    return *this;
}

MenuItem* MenuItem::Builder::build() {
    return new MenuItem(_text, _children, _parent, _renderable, _quit);
}
