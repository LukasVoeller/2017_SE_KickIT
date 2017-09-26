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
	 * @param VirtualKickerWindow* vkw
	 *
	 */
	TableControllerImpl(VirtualKickerWindow* vkw);

	/**setBallPos funktion
	 * @param float x, float y
	 *
	 */
	void setBallPos(float x, float y);

	/**poxelToMM function
	 * @param float xPixel, float yPixel
	 * @return result
	 *
	 * the function gets pixes as a parameter and converts it into milimeters
	 */
	Vec2 pixelToMM(float xPixel, float yPixel);

protected:
	VirtualKickerWindow* vkw;

signals:
	/**newBallStatus function
	 * @param BallStatus bs
	 */
	void newBallStatus(BallStatus bs);

};

#endif //TABLECONTROLLERIMPL_HPP

