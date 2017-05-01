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

    /**
     * @brief
     *      Init Object from some source
     * @return
     */
    inline virtual bool initObject() { return true; }

    virtual bool drawFigure() override;

    virtual bool eraseFigure() override;

    virtual game::Point getPos() override;

    virtual bool setPos(unsigned y, unsigned x) override;

    virtual ObjectType getType() const override;

    virtual bool setType(ObjectType) override;

    virtual bool move(unsigned nSigns, Direction direction);

protected:
    const std::string m_objectName;
    const ObjectASCII *m_signs;
    unsigned m_xShift, m_yShift;
    ObjectType m_type;
};

}
#endif //GAME_OBJECTIMPL_H
