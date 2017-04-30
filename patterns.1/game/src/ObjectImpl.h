//
// Created by avk on 30.04.17.
//

#ifndef GAME_OBJECTIMPL_H
#define GAME_OBJECTIMPL_H

#include <IObject.h>
#include <string>
#include <vector>


class Object : public IObject {
public:
    Object() { return; };
    /**
     * @brief
     *      Init Object from some source
     * @return
     */
    inline virtual bool initFigure() { return true; }

    virtual bool drawFigure() override;
    virtual bool eraseFigure() override;
    virtual bool setPos(unsigned y, unsigned x) override;

protected:
    std::string m_objectName;
    std::vector<std::string>* m_signs;
    unsigned m_xShift, m_yShift;
};

#endif //GAME_OBJECTIMPL_H
