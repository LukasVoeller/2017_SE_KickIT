#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "InterfaceRowController.hpp"
#include "InterfaceTableController.hpp"
#include "../DataType/BallStatus.hpp"

class TableControllerImpl : public InterfaceTableController{
private:
	BallStatus currentBallStaus;
	bool keeperActive, defenseActive, midfieldActive, offenseActive;
	InterfaceRowController* keeperControl;
	InterfaceRowController* defenseControl;
	InterfaceRowController* midfieldControl;
	InterfaceRowController* offenseControl;
public:
	TableControllerImpl(bool keeper, bool defense, bool midfield, bool offense);
	void setBallStatus(BallStatus* b);
	void run();
	void stop();
};

#endif /* TABLECONTROLLERIMPL_HPP */

