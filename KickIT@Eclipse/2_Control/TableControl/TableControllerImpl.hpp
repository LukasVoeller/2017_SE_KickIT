/**
 * @file TableControllerImpl.hpp
 * @brief
 */
#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "../../3_VirtualKicker/VirtualKickerWindow.hpp"
#include "../2_Control/TableControl/_TableControllerInterface.hpp"
#include <QObject>

/**TableControllerImpl class
 *
 */
class TableControllerImpl : public QObject,  public TableControllerInterface {
	Q_OBJECT

public:
	/**TableControllerImpl constructor
	 *
	 * @param VirtualKickerWindow* vkw
	 *
	 */
	TableControllerImpl(VirtualKickerWindow* vkw);

	void setBallPos(float x, float y);
	Vec2 pixelToMM(float xPixel, float yPixel);
protected:
	VirtualKickerWindow* vkw;

signals:
	/**newBallStatus function
	 *
	 * @param BallStatus bs
	 */
	void newBallStatus(BallStatus bs);

};

#endif //TABLECONTROLLERIMPL_HPP

