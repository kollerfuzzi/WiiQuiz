#ifndef CONFIRM_HPP
#define CONFIRM_HPP

#include "renderable.hpp"
#include "wiimote.hpp"
#include "textbox.hpp"
#include "resources.hpp"

class Confirm : public Renderable {
public:
    Confirm(Resources* resources, std::string prompt,
            Remote remote, Button button, bool enabled);
    ~Confirm();
    void update(const Clock& clock);
    void render();
    bool isConfirmed();
    void setEnabled(bool enabled);

    class Builder {
    public:
        Builder& resources(Resources* resources);
        Builder& prompt(std::string prompt);
        Builder& remote(Remote remote);
        Builder& button(Button button);
        Builder& enabled(bool enabled);
        Confirm* build();
    private:
        std::string _prompt = "Press A to continue";
        Remote _remote = Remote::R1;
        Button _button = Button::A;
        Resources* _resources;
        bool _enabled = true;
    };
    static Builder builder();
private:
    void _init();
    bool _initialized = false;
    bool _confirmed = false;
    bool _enabled;
    std::string _prompt;
    Remote _remote;
    Button _button;
    TextBox* _promptTextbox = nullptr;
    Resources* _resources;
};

#endif // CONFIRM_HPP
