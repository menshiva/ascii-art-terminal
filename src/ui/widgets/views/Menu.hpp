#ifndef ASCIIART_MENU_HPP
#define ASCIIART_MENU_HPP

#include <vector>
#include <memory>
#include "../containers/MultiViewContainer.hpp"
#include "../containers/Pos.hpp"

class Menu : public MultiViewContainer {
public:
    explicit Menu(uint8_t rows, uint8_t cols, uint16_t rowsSpace, uint16_t colsSpace) :
        MultiViewContainer(),
        m_Rows(rows), m_Cols(cols),
        m_RowsSpace(rowsSpace), m_ColsSpace(colsSpace) {}

    uint16_t getHeight() const override {
        uint16_t res = 0;
        for (uint8_t r = 0; r < m_Rows; ++r) {
            uint16_t maxRowH = 0;
            for (uint8_t c = 0; c < m_Cols; ++c) {
                const auto &view = m_Positions[r * m_Cols + c]->getChild();
                uint16_t h = view->getHeight();
                if (h > maxRowH)
                    maxRowH = h;
            }
            res += maxRowH;
        }
        return res;
    }

    uint16_t getWidth() const override {
        uint16_t res = 0;
        for (uint8_t r = 0; r < m_Rows; ++r) {
            uint16_t rowW = 0;
            for (uint8_t c = 0; c < m_Cols; ++c) {
                const auto &view = m_Positions[r * m_Cols + c]->getChild();
                rowW += view->getWidth();
            }
            if (rowW > res)
                res = rowW;
        }
        return res;
    }

    uint16_t getY() const override {
        return getParent()->getY();
    }

    uint16_t getX() const override {
        return getParent()->getX();
    }

    void draw() override {
        uint16_t y = getY();
        for (uint8_t r = 0; r < m_Rows; ++r) {
            uint16_t x = getX();
            for (uint8_t c = 0; c < m_Cols; ++c) {
                const auto &pos = m_Positions[r * m_Cols + c];
                pos->setY(y);
                pos->setX(x);
                x += m_ColsSpace + 1;
            }
            y += m_RowsSpace + 1;
        }
        MultiViewContainer::draw();
    }

    void setChild(View *child) override {
        m_Positions.emplace_back(new Pos());
        m_Positions.back()->setChild(child);
        MultiViewContainer::setChild(m_Positions.back().get());
    }
private:
    std::vector<std::unique_ptr<Pos>> m_Positions;
    uint8_t m_Rows, m_Cols;
    uint16_t m_RowsSpace, m_ColsSpace;
};

#endif //ASCIIART_MENU_HPP
