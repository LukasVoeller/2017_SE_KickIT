#ifndef INTERFACETABLECONTROLLER_HPP
#define INTERFACETABLECONTROLLER_HPP

#include "../Interface/RowControllerInterface.hpp"
#include "../DataType/BallStatus.hpp"
#include "../DataType/BallStatus.hpp"
#include "../DataType/Vec2.hpp"
#include <iostream>

class TableControllerInterface {

public:
	virtual void setBallPos(float x, float y) = 0;
	virtual void run() = 0;
	virtual void stop() = 0;
	virtual ~TableControllerInterface() {}

	void motorByHand() {
		std::cout << "motorByHand()" << std::endl;

		int position = 1;
		int row = 1;

		while (row != -1) {
			position = 1;
			std::cout
					<< "Enter row [1:Keeper] [2:Defense] [3:Both] (Exit with -1): ";
			std::cin >> row;

			while (position != -1) {
				std::cout << "Enter position (Exit with -1): ";
				std::cin >> position;

				if (row == 1) {
					if (isKeeperActive) {
						keeperControl->moveTo(position);
					} else {
						std::cout << "Keeper is not active" << std::endl;
					}
				}

				if (row == 2) {
					if (isDefenseActive) {
						defenseControl->moveTo(position);
					} else {
						std::cout << "Defense is not active" << std::endl;
					}
				}

				if (row == 3) {
					if (isDefenseActive && isKeeperActive) {
						defenseControl->moveTo(position);
						keeperControl->moveTo(position);
					} else {
						std::cout << "One or both are not active" << std::endl;
					}
				}
			}
		}
	}

protected:
	BallStatus ballStatus;
	bool isKeeperActive;
	bool isDefenseActive;
	bool isMidfieldActive;
	bool isOffenseActive;

	BallStatus currentBallStaus;
	RowControllerInterface* keeperControl;
	RowControllerInterface* defenseControl;
	RowControllerInterface* midfieldControl;
	RowControllerInterface* offenseControl;

	float* calculateRowPositions(float tableHeight, BallStatus* b, bool keeper,
			bool defense, bool midfield, bool offense, float yOffset = 0,
			float dDist = 0, float mDist = 0, float oDist = 0,
			Vec2* keeperPositionalVector = 0, Vec2* defensePositionalVector = 0,
			Vec2* midfieldPositionalVector = 0, Vec2* offensePositionalVector =
					0) {

		Vec2 rowDirectionalVector(0, -1);
		rowDirectionalVector.normalize();
		b->movement.normalize();

		float* result = new float[keeper ? 1 : 0 + defense ? 1 :
									0 + midfield ? 1 : 0 + offense ? 1 : 0];
		if (keeper) {
			float cross = b->movement.cross(rowDirectionalVector);

			if (cross != 0) {
				float factor = ((*keeperPositionalVector - b->movement).cross(
						rowDirectionalVector)) / cross;

				result[0] = (b->position + b->movement * (-factor)).y;

				//Vec2 C(rowDirectionalVector-b->position);
				//result[0] = (rowDirectionalVector.x*C.y - rowDirectionalVector.y*C.x) / cross;
			} else {
				//std::cout << "No intersection" << std::endl;
				result[0] = b->position.y;
			}
		}

		if (defense) {
			//TODO Aehnliche berechnung des schnittpunktes wie beim keeper

			float pos = 0;

			if (b->position.y < (tableHeight / 2 + yOffset)) {
				pos = b->position.y;
			} else {
				pos = b->position.y - dDist;
				result[1] = pos;
			}
		}

		//TODO Speicherlecks
		delete keeperPositionalVector;

		return result;
	}

	void updateBallStatus(float x, float y) {
		ballStatus.movement.x = ballStatus.position.x - x;
		ballStatus.movement.y = ballStatus.position.y - y;
		ballStatus.position.update(x, y);
	}
};

#endif //INTERFACETABLECONTROLLER_HPP
