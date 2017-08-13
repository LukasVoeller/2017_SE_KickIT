#ifndef INTERFACETABLECONTROLLER_HPP
#define INTERFACETABLECONTROLLER_HPP

#include "../Interface/RowControllerInterface.hpp"
#include "../DataType/BallStatus.hpp"
#include "../DataType/BallStatus.hpp"
#include "../DataType/Vec2.hpp"
#include <iostream>
#include "../Calculation/PositionCalculator.hpp"

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

	PositionCalculator* calc;

	BallStatus currentBallStaus;
	RowControllerInterface* keeperControl;
	RowControllerInterface* defenseControl;
	RowControllerInterface* midfieldControl;
	RowControllerInterface* offenseControl;

	/*void updateBallStatus(float x, float y) {
		ballStatus.movement.x = ballStatus.position.x - x;
		ballStatus.movement.y = ballStatus.position.y - y;
		ballStatus.position.update(x, y);
	}*/
};

#endif //INTERFACETABLECONTROLLER_HPP
