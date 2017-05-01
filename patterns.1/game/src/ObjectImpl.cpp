//
// Created by avk on 30.04.17.
//

#include <ncurses.h>
#include "ObjectImpl.h"

namespace game {

///////////////////////////////////////////////////////////////////////////////

    bool Object::drawFigure() {
        std::size_t lines_number = m_signs->size();
        for (unsigned line_no = 0; line_no < lines_number; ++line_no) {
            const std::string *line = &m_signs->at(line_no);
            // Move && print something.
            mvprintw(m_yShift + line_no, m_xShift, line->c_str());
        }
        return true;
    }

///////////////////////////////////////////////////////////////////////////////

    bool Object::eraseFigure() {
        std::size_t lines_number = m_signs->size();
        for (unsigned line_no = 0; line_no < lines_number; ++line_no) {
            std::string spaces = std::string(m_signs->at(line_no).size(), ' ');
            mvprintw(m_yShift + line_no, m_xShift, spaces.c_str());
        }

        return true;
    }

///////////////////////////////////////////////////////////////////////////////

    bool Object::setPos(ShiftType y, ShiftType x) {
        m_yShift = y;
        m_xShift = x;
        return true;
    }

    Object::Object(const ObjectName &name,
                   const ObjectASCII *repr, ObjectType type,
                   ObjectShift y_pos, ObjectShift x_pos)
            : m_objectName(name),
              m_type(type),
              m_signs(repr),
              m_yShift(y_pos),
              m_xShift(x_pos) {}

    bool Object::move(ShiftType nSigns, Direction direction) {
        switch (direction) {
            case Direction::left: {
                m_xShift -= nSigns;
                break;
            }
            case Direction::right: {
                m_xShift += nSigns;
                break;
            }
            case Direction::up: {
                m_yShift -= nSigns;
                break;
            }
            case Direction::down: {
                m_yShift += nSigns;
                break;
            }
            default: {
                break;
                // Todo : implement other directions if needed.
            }
        }
        return false;
    }

///////////////////////////////////////////////////////////////////////////////

    game::Point Object::getPos() {
        return game::Point(m_yShift, m_xShift);
    }

///////////////////////////////////////////////////////////////////////////////

    ObjectType Object::getType() const {
        return m_type;
    }

    bool Object::setType(ObjectType type) {
        m_type = type;
        return true;
    }

}
