#ifndef INTERFACETABLECONTROLLER_HPP
#define INTERFACETABLECONTROLLER_HPP

#include "../RowControl/_RowControllerInterface.hpp"
#include <iostream>

#include "../../4_Utilities/Calculator.hpp"
#include "../../4_Utilities/Modules.hpp"
#include "../../5_DataType/BallStatus.hpp"
#include "../../5_DataType/Vec2.hpp"
#include "../../5_DataType/BallStatus.hpp"
#include "../../5_DataType/CameraConfig.hpp"
#include "../../5_DataType/TableConfig.hpp"

class TableControllerInterface {

public:
	virtual void setBallPos(float x, float y) = 0;
	virtual ~TableControllerInterface() {
		delete this->keeperControl;
		delete this->defenseControl;
		delete this->midfieldControl;
		delete this->offenseControl;
	}

	void motorByHand() {
		std::cout << "MOTOR BY HAND" << std::endl;

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
					if (tc.isKeeperActive) {
						keeperControl->moveTo(position);
					} else {
						std::cout << "Keeper is not active" << std::endl;
					}
				}

				if (row == 2) {
					if (tc.isDefenseActive) {

						if(position == 1){
							defenseControl->kick(0);
						}else{
							defenseControl->moveTo(position);
						}

					} else {
						std::cout << "Defense is not active" << std::endl;
					}
				}

				if (row == 3) {
					if (tc.isDefenseActive && tc.isKeeperActive) {
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
	CameraConfig cc;
	TableConfig tc;
	BallStatus ballStatus;

	BallStatus currentBallStaus;
	RowControllerInterface* keeperControl;
	RowControllerInterface* defenseControl;
	RowControllerInterface* midfieldControl;
	RowControllerInterface* offenseControl;

	virtual Vec2 pixelToMM(float xPixel, float yPixel) = 0;

	/*Backup
	void updateBallStatus(float x, float y) {
		ballStatus.movement.x = ballStatus.position.x - x;
		ballStatus.movement.y = ballStatus.position.y - y;
		ballStatus.position.update(x, y);
	}
	*/
};

#endif //INTERFACETABLECONTROLLER_HPP
