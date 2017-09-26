/**
 * @file TableControllerMock.hpp
 * @brief
 */
#ifndef TABLECONTROLLERMOCK_HPP
#define TABLECONTROLLERMOCK_HPP

#include "../3_VirtualKicker/VirtualKickerWindow.hpp"
#include "../5_DataType/Vec2.hpp"
#include "../2_Control/TableControl/_TableControllerInterface.hpp"

/**TableControllerMock class
 *
 */
class TableControllerMock: public TableControllerInterface {

public:
	/**TableControllerMock constructor
	 *
	 */
	TableControllerMock();

	/**TableControllerMock destructor
	 *
	 */
	virtual ~TableControllerMock();

	/**run function
	 *
	 */
	void run();

	/**stop function
	 *
	 */
	void stop();
	void setBallPos(float x, float y);

	/**setKickerWindow function
	 *
	 * @param VirtualKickerWindow* p
	 *
	 */
	void setKickerWindow(VirtualKickerWindow* p);

protected:
	virtual Vec2 pixelToMM(float xPixel, float yPixel){}
	VirtualKickerWindow* window;
};

#endif //TABLECONTROLLERMOCK_HPP
