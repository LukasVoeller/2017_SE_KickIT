

#include "TableControllerImpl.hpp"
#include "RowControllerKeeper.hpp"

TableControllerImpl::TableControllerImpl(bool keeper, bool defense, bool midfield, bool offense):keeperActive(keeper), defenseActive(defense), midfieldActive(midfield), offenseActive(offense){

	if(keeperActive){
		//initiate connection to the keeper-driver
		keeperControl = new RowControllerKeeper();
	}
}


