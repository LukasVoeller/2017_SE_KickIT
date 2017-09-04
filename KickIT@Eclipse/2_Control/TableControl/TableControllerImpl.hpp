#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "../../3_VirtualKicker/VirtualKickerWindow.hpp"
#include "../2_Control/TableControl/_TableControllerInterface.hpp"
#include <QObject>

class TableControllerImpl : public QObject,  public TableControllerInterface {
	Q_OBJECT

public:
	TableControllerImpl(VirtualKickerWindow* vkw);
	void setBallPos(float x, float y);
	Vec2 pixelToMM(float xPixel, float yPixel);
protected:
	VirtualKickerWindow* vkw;

signals:
	void newBallStatus(BallStatus bs);

};

#endif //TABLECONTROLLERIMPL_HPP

