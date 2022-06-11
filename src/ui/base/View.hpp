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
    typedef int8_t Id;
    const static Id UNUSED_ID = -1;

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

    virtual void interact(int key) const;
protected:
    View() : m_ParentContainer(nullptr) {}
    virtual void draw() = 0;
protected:
    Container *m_ParentContainer;
    std::function<uint16_t()> m_GetHeight, m_GetWidth;
    std::function<uint16_t()> m_GetY, m_GetX;
};

class Container : public View {
    friend class View;
public:
    struct Child {
        Child(Id id, View *view) : id(id), view(view) {}
        Child(View *view) : Child(UNUSED_ID, view) {} // NOLINT(google-explicit-constructor)
        Id id;
        View *view;
    };

    struct ChildData {
        ChildData(Id id, View *view) : id(id), view(view) {}
        Id id;
        std::unique_ptr<View> view;
    };

    Container *withWrapContent();

    virtual WINDOW *getWindow() const = 0;
    virtual Container *withChildren(std::initializer_list<Child> children);
    void interact(int key) const override;
    virtual void onChildWithId(Id id, View* child) = 0;
protected:
    Container() : View() {}
    void draw() override;
protected:
    std::vector<ChildData> m_Children;
};

#endif //ASCIIART_VIEW_HPP
