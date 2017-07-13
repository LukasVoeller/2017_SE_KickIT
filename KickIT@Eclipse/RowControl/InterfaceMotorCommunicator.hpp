#ifndef INTERFACEMOTORCOMMUNICATOR_HPP
#define INTERFACEMOTORCOMMUNICATOR_HPP

class InterfaceMotorCommunicator{
	public:
	virtual void moveTo(float y) = 0;
	virtual void kick() = 0;

	private:
	virtual void homing() = 0;
};

#endif /* INTERFACEMOTORCOMMUNICATOR_HPP */

