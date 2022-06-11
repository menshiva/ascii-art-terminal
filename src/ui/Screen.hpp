#ifndef ASCIIART_SCREEN_HPP
#define ASCIIART_SCREEN_HPP

#include <unordered_map>
#include <panel.h>
#include "containers/Panel.hpp"
#include "containers/Menu.hpp"
#include "views/Text.hpp"
#include "views/Space.hpp"

class Screen final : public Container {
public:
    static bool init();

    Screen();
    ~Screen() override;

    void mainLoop();
    void markDirty();
    void close();

    WINDOW *getWindow() const override;
    Screen *withChildren(std::initializer_list<Child> children) override;
    void onChildWithId(Id id, View *child) override;

    template<class T>
    T *getView(Id id) {
        return dynamic_cast<T*>(m_Views.at(id));
    }
protected:
    void draw() override;
private:
    bool m_MainLoopRunning, m_WindowDirty;
    std::unordered_map<Id, View*> m_Views;
};

#endif //ASCIIART_SCREEN_HPP
