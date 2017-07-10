
#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "TableControllerInterface.hpp"
#include "RowControllerInterface.hpp"

#include "../DataType/BallStatus.hpp"

class TableControllerImpl : public TableControllerInterface{
private:
	bool keeperActive, defenseActive, midfieldActive, offenseActive;
	RowControllerInterface* keeperControl, defenseControl, midfieldControl, offenseControl;
public:
	TableControllerImpl(bool keeper, bool defense, bool midfield, bool offense);
	void setBallStatus(BallStatus* b){};
};


#endif /* TABLECONTROLLERIMPL_HPP */

