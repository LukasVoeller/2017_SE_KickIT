
#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "TableControllerInterface.hpp"

class TableControllerImpl : public TableControllerInterface{
	public:
	TableControllerImpl(bool keeper, bool defense, bool midfield, bool offense);
};


#endif /* TABLECONTROLLERIMPL_HPP */

