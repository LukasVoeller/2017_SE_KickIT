/*
 * RowContoller.hpp
 *
 *  Created on: 23.03.2017
 *      Author: student
 */

#ifndef ROWCONTROLLERIMPL_HPP_
#define ROWCONTROLLERIMPL_HPP_
#include "RowControllerInterface.hpp"
#include "../DataType/BallStatus.hpp"
#include <pthread.h>

class RowControllerImpl : public RowControllerInterface{
    
    private:
        pthread_t id;
    
    public:
        RowControllerImpl();
	void run();
};

#endif /* ROWCONTROLLER_HPP_ */
