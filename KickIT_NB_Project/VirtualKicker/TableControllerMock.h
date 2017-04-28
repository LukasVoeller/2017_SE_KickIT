

#ifndef TABLECONTROLLERMOCK_H
#define TABLECONTROLLERMOCK_H

#include "../RowControl/TableControllerInterface.hpp"

class TableControllerMock : public TableControllerInterface{
public:
    TableControllerMock();
    TableControllerMock(const TableControllerMock& orig);
    virtual ~TableControllerMock();
private:

};

#endif /* TABLECONTROLLERMOCK_H */

