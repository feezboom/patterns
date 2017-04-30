//
// Created by avk on 30.04.17.
//

#ifndef GAME_OBJECTIMPL_H
#define GAME_OBJECTIMPL_H

#include <IObject.h>
#include <string>
#include <vector>
#include <context.h>


class Object : public IObject {
public:
    Object(const ObjectName& name, const ObjectRepresentation* repr,
           ObjectShift y_pos, ObjectShift x_pos);
    /**
     * @brief
     *      Init Object from some source
     * @return
     */
    inline virtual bool initFigure() { return true; }

    virtual bool drawFigure() override;
    virtual bool eraseFigure() override;
    virtual bool setPos(unsigned y, unsigned x) override;
    virtual bool move(unsigned nSigns, Direction direction);

protected:
    const std::string m_objectName;
    const ObjectRepresentation* m_signs;
    unsigned m_xShift, m_yShift;
};

#endif //GAME_OBJECTIMPL_H
