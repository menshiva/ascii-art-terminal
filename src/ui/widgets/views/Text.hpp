#ifndef ASCIIART_TEXT_HPP
#define ASCIIART_TEXT_HPP

#include <cstring>
#include "../View.hpp"

class Text : public View {
public:
    Text(float yRelative, float xRelative, const char *text, bool centered);
    Text(View *parent, float yRelative, float xRelative, const char *text, bool centered);

    WINDOW *getWindow() const override;
    uint16_t getHeight() const override;
    uint16_t getWidth() const override;

    void resize() override;
    void draw() override;
private:
    bool m_CenteredInParent;
    const char *m_Text;
};

#endif //ASCIIART_TEXT_HPP
