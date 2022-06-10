#ifndef ASCIIART_VIEW_HPP
#define ASCIIART_VIEW_HPP

#include <functional>
#include <vector>
#include <memory>
#include <curses.h>

class Container;

class View {
public:
    View();
    virtual ~View() = default;

    View(const View&) = delete;
    View &operator=(const View&) = delete;
    View(View&&) = delete;
    View &operator=(View&&) = delete;

    const Container *getParentContainer() const;
    void setParentContainer(Container *container);

    uint16_t getHeight() const;
    uint16_t getWidth() const;
    uint16_t getY() const;
    uint16_t getX() const;

    View *setHeight(const std::function<uint16_t()> &f);
    View *setWidth(const std::function<uint16_t()> &f);
    View *setAbsoluteHeight(uint16_t h);
    View *setAbsoluteWidth(uint16_t w);
    View *setRelativeParentHeight(float hRel);
    View *setRelativeParentWidth(float wRel);

    View *setY(const std::function<uint16_t()> &f);
    View *setX(const std::function<uint16_t()> &f);
    View *setAbsoluteY(uint16_t y);
    View *setAbsoluteX(uint16_t x);
    View *setCenteredInParentHeight();
    View *setCenteredInParentWidth();
    View *attachToChildInParentBelow(bool fillSize, size_t childIdx);
    View *attachToChildInParentRight(bool fillSize, size_t childIdx);

    virtual void draw() = 0;
    virtual void interact(int c) const;
    virtual bool isActive() const;
private:
    Container *m_ParentContainer;
    std::function<uint16_t()> m_GetHeight, m_GetWidth;
    std::function<uint16_t()> m_GetY, m_GetX;
};

class Container : public View {
public:
    friend class View;

    Container(std::initializer_list<View*> children);

    virtual WINDOW *getWindow() const = 0;

    void draw() override;
    void interact(int c) const override;
protected:
    std::vector<std::unique_ptr<View>> m_Children;
};

#endif //ASCIIART_VIEW_HPP
