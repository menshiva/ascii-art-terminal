#ifndef ASCIIART_VIEW_HPP
#define ASCIIART_VIEW_HPP

#include <cstdint>
#include <curses.h>

class View {
public:
    virtual ~View() = default;

    View(const View&) = delete;
    View &operator=(const View&) = delete;
    View(View&&) = delete;
    View &operator=(View&&) = delete;

    virtual WINDOW *getWindow() const = 0;
    virtual uint16_t getHeight() const = 0;
    virtual uint16_t getWidth() const = 0;

    void setParent(View *parent) {
        m_Parent = parent;
    }

    virtual void resize() = 0;
    virtual void draw() = 0;
protected:
    View(float heightRelative, float widthRelative,
         float yRelative, float xRelative
    ) : m_Parent(nullptr),
        m_HeightRel(heightRelative), m_WidthRel(widthRelative),
        m_YRel(yRelative), m_XRel(xRelative) {}

    View(View *parent,
         float heightRelative, float widthRelative,
         float yRelative, float xRelative
    ) : m_Parent(parent),
        m_HeightRel(heightRelative), m_WidthRel(widthRelative),
        m_YRel(yRelative), m_XRel(xRelative) {}
protected:
    View *m_Parent;
    float m_HeightRel, m_WidthRel;
    float m_YRel, m_XRel;
};

#endif //ASCIIART_VIEW_HPP
