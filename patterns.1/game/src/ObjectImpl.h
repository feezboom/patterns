//
// Created by avk on 30.04.17.
//

#ifndef GAME_OBJECTIMPL_H
#define GAME_OBJECTIMPL_H

#include <string>
#include <vector>

#include <IObject.h>
#include <context.h>

namespace game {

class Object : public IObject {
public:
    Object(const ObjectName &name, const ObjectASCII *repr,
           ObjectType type = ObjectType::eUndefined,
           ObjectShift y_pos = 0, ObjectShift x_pos = 0);

    virtual bool drawFigure() override;

    virtual bool eraseFigure() override;

    virtual game::Point getPos() override;

    virtual bool setPos(ShiftType y, ShiftType x) override;

    virtual ObjectType getType() const override;

    virtual bool setType(ObjectType) override;

    virtual bool move(ShiftType nSigns, Direction direction);

    virtual const ObjectASCII* getASCIIRepresentation() override;

//protected:
    public:

    const std::string m_objectName;
    const ObjectASCII *m_signs;
    ShiftType m_xShift, m_yShift;
    ObjectType m_type;
};

}
#endif //GAME_OBJECTIMPL_H
