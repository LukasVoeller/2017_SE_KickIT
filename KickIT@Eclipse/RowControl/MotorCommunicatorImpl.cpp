

#include "MotorCommunicatorImpl.hpp"

bool MotorCommunicatorImpl::openPort(const char* port){
    /*struct ifreq ifr;
    struct sockaddr_can addr;

    
    this->socketId = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (socket < 0)
            return -1;

    addr.can_family = AF_CAN;
    
    //strcpy(ifr.ifr_name, port); //c++ functions!!
    
    if (ioctl(socketId, SIOCGIFINDEX, &ifr) < 0)
            return (-1);
    addr.can_ifindex = ifr.ifr_ifindex;
    fcntl(socketId, F_SETFL, O_NONBLOCK);
    if (bind(socketId, (struct sockaddr *) &addr, sizeof(addr)) < 0)
            return -1;
*/
    return 0;
}