#ifndef ASCII_TEXT_HPP
#define ASCII_TEXT_HPP

#include <string>
#include "View.hpp"

class Text : public View {
    std::string text;
public:
    Text(View *parent, std::string text, float yRelative, float xRelative);
    Text(const Text &) = delete;
    Text &operator=(const Text &) = delete;
    Text(Text &&) = delete;
    Text &operator=(Text &&) = delete;
    ~Text() override = default;

    void changeText(const std::string &newText);

    WINDOW *getWindow() const override;
    size_t getHeight() const override;
    size_t getWidth() const override;

    void draw() override;
    void resize() override;
    void show() override;
    void hide() override;
};

#endif