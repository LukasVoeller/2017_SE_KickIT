#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "InterfaceRowController.hpp"
#include "InterfaceTableController.hpp"
#include "../DataType/BallStatus.hpp"

class TableControllerImpl: public InterfaceTableController {

public:
	TableControllerImpl(bool keeper, bool defense, bool midfield, bool offense);
	void setBallPos(float x, float y);
	void run();
	void stop();

private:
	BallStatus currentBallStaus;

	InterfaceRowController* keeperControl;
	InterfaceRowController* defenseControl;
	InterfaceRowController* midfieldControl;
	InterfaceRowController* offenseControl;
};

#endif /* TABLECONTROLLERIMPL_HPP */

