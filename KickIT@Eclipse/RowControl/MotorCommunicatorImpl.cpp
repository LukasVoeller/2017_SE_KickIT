#include "MotorCommunicatorImpl.hpp"
#include <iostream>
#include <cstring>

MotorCommunicatorImpl::MotorCommunicatorImpl(Row r){
	//TODO Verbindungsaufbau

	switch(r){
		case KEEPER:
			std::cout << "Connecting to keeper driver...";
			if(openPort("can0") == 0)
				std::cout << " done!" << std::endl;
			else
				std::cout << " failed" << std::endl;
			break;
		case DEFENSE:
			std::cout << "Connecting to defense driver...";
			if(openPort("can0") == 0)	//Auch can0 wie bei Keeper?
				std::cout << " done!" << std::endl;
			else
				std::cout << " failed" << std::endl;
			break;
		case MIDFIELD:
			std::cout << "Connecting to midfield driver...";
			if(openPort("can0") == 0)	//Auch can0 wie bei Keeper?
				std::cout << " done!" << std::endl;
			else
				std::cout << " failed" << std::endl;
			break;
		case OFFENSE:
			std::cout << "Connecting to offense driver...";
			if(openPort("can0") == 0)	//Auch can0 wie bei Keeper?
				std::cout << " done!" << std::endl;
			else
				std::cout << " failed" << std::endl;
			break;
	}
}

int MotorCommunicatorImpl::openPort(const char* port){
    struct ifreq ifr;
    struct sockaddr_can addr;

    socketId = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    
    if (socket < 0)
		return -1;

    addr.can_family = AF_CAN;
    strcpy(ifr.ifr_name, port); //C++ functions!
    
    if (ioctl(socketId, SIOCGIFINDEX, &ifr) < 0)
		return -1;
    
    addr.can_ifindex = ifr.ifr_ifindex;
    fcntl(socketId, F_SETFL, O_NONBLOCK);

    if (bind(socketId, (struct sockaddr *) &addr, sizeof(addr)) < 0)
		return -1;

    homing();
    return 0;
}

void MotorCommunicatorImpl::homing(){

}

void MotorCommunicatorImpl::moveTo(float y){

}

void MotorCommunicatorImpl::kick(){

}
