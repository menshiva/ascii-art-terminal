#ifndef ASCIIART_VIEW_HPP
#define ASCIIART_VIEW_HPP

#include <functional>
#include <vector>
#include <memory>
#include <curses.h>

class Container;

class View {
    friend class Container;
public:
    virtual ~View() = default;

    View(const View&) = delete;
    View &operator=(const View&) = delete;
    View(View&&) = delete;
    View &operator=(View&&) = delete;

    uint16_t getHeight() const;
    uint16_t getWidth() const;
    uint16_t getY() const;
    uint16_t getX() const;

    View *withHeight(const std::function<uint16_t()> &f);
    View *withWidth(const std::function<uint16_t()> &f);
    View *withAbsoluteHeight(uint16_t h);
    View *withAbsoluteWidth(uint16_t w);
    View *withRelativeHeight(float hRel);
    View *withRelativeWidth(float wRel);

    View *withY(const std::function<uint16_t()> &f);
    View *withX(const std::function<uint16_t()> &f);
    View *withAbsoluteY(uint16_t y);
    View *withAbsoluteX(uint16_t x);
    View *withCenteredInParentHeight();
    View *withCenteredInParentWidth();
    View *withAttachedBelow(bool fillSize, size_t childIdx);
    View *withAttachedRight(bool fillSize, size_t childIdx);

    virtual bool isActive() const;
    virtual void interact(int key) const;
protected:
    View();
    virtual void draw() = 0;
protected:
    Container *m_ParentContainer;
    std::function<uint16_t()> m_GetHeight, m_GetWidth;
    std::function<uint16_t()> m_GetY, m_GetX;
};

class Container : public View {
    friend class View;
public:
    virtual WINDOW *getWindow() const = 0;
    virtual Container *withChildren(std::initializer_list<View*> children);
    void interact(int key) const override;
protected:
    Container();

    void addChild(View *child);

    void draw() override;
protected:
    std::vector<std::unique_ptr<View>> m_Children;
};

#endif //ASCIIART_VIEW_HPP
