#ifndef INTERFACEMOTORCOMMUNICATOR_HPP
#define INTERFACEMOTORCOMMUNICATOR_HPP

class MotorCommunicatorInterface {
public:
	virtual void moveTo(float y) = 0;	//Redundant?
	virtual void kick() = 0;			//Redundant?

private:
	virtual int openPort(const char* port) = 0;
	virtual int closePort() = 0;
	virtual int sendPort(struct can_frame* frame) = 0;
	virtual void readPort() = 0;
	virtual void frameInit(int ID, int DLC, int Data_0, int Data_1, int Data_2,
			int Data_3, int Data_4, int Data_5, int Data_6, int Data_7) = 0;
	virtual void driverInit() = 0;
	virtual void motorSwitchon() = 0;
	virtual void homing() = 0;
	//virtual void motorByHand() = 0;
	//virtual void linearMovement(int positionL) = 0;
	//virtual void shootingMove(int positionS) = 0;

protected:
	char* port;		//Redundant?
	//TODO Socket_id
};

#endif /* INTERFACEMOTORCOMMUNICATOR_HPP */
