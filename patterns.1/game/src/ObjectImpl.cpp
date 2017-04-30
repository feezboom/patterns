//
// Created by avk on 30.04.17.
//

#include <ncurses.h>
#include "ObjectImpl.h"

bool Object::drawFigure() {
    std::size_t lines_number = m_signs.size();
    for (unsigned line_no = 0; line_no < lines_number; ++line_no) {
        std::string* line = &m_signs[line_no];
        // Move && print something.
        mvprintw(m_yShift + line_no, m_xShift, line->c_str());
    }
    return true;
}

bool Object::eraseFigure() {
    std::size_t lines_number = m_signs.size();
    for (unsigned line_no = 0; line_no < lines_number; ++line_no) {
        std::string spaces = std::string(m_signs.size(), ' ');
        mvprintw(m_yShift + line_no, m_xShift, spaces.c_str());
    }

    return true;
}

bool Object::setPos(unsigned y, unsigned x) {
    m_yShift = y;
    m_xShift = x;
    return true;
}
