#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "../DataType/BallStatus.hpp"
#include "../Interface/RowControllerInterface.hpp"
#include "../Interface/TableControllerInterface.hpp"

class TableControllerImpl: public TableControllerInterface {

public:
	TableControllerImpl(bool keeper, bool defense, bool midfield, bool offense);
	void setBallPos(float x, float y);
	void run();
	void stop();

private:
	BallStatus currentBallStaus;

	RowControllerInterface* keeperControl;
	RowControllerInterface* defenseControl;
	RowControllerInterface* midfieldControl;
	RowControllerInterface* offenseControl;
};

#endif /* TABLECONTROLLERIMPL_HPP */

