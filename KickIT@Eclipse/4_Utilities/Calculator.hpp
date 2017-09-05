
#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "../5_DataType/Vec2.hpp"
#include "../5_DataType/TableConfig.hpp"
#include "../5_DataType/BallStatus.hpp"

#include <vector>

namespace Calculator {
	static TableConfig tc;
	static Vec2 rowDirectionalVector(0, 1);
	static Vec2 keeperPosition(tc.distGoalToKeeper, 0);

	static void calcPositionsSimple(std::vector<void*>* params) {

		BallStatus* bs = ((BallStatus*)params->at(0));
		float* positions = ((float*)params->at(1));

		//std::cout << "bs: " << bs->position.y << std::endl;
		if (tc.isKeeperActive) {
			if ( bs->movement.x < 0 ) {
				float m = bs->movement.y / bs->movement.x;
				m*=(-1);
				float pos = ((bs->position.x - tc.distGoalToKeeper) * m) + bs->position.y;
				positions[0] = pos;
			}else if ( bs->movement.x > 0) {
				//std::cout << "positions[0] " << 340 << std::endl;
				positions[0] = 340;
			}else if (bs->movement.x == 0){
				//std::cout << "positions[0] " << bs->position.y << std::endl;
				positions[0] = bs->position.y;
			}
		}

		if (tc.isDefenseActive) {

			if ( bs->movement.x < 0 ) {

				float m = bs->movement.y / bs->movement.x;
				m*=(-1);
				float pos = ((bs->position.x - tc.distGoalToDefense) * m) + bs->position.y;
				positions[1] = pos;
			}
			if ( bs->movement.x > 0) {
				positions[1] = 200;
			}

		}

	}

	static void calcIfKickSimple(std::vector<void*>* params) {
		BallStatus* bs = ((BallStatus*)params->at(0));
		bool* kick = ((bool*)params->at(3));
		if(bs->position.x < 350 && bs->position.x > 180 && bs->movement.x < 0){
			kick[0] = true;
		} else {
			kick[0] = false;
		}

	}

	static void calcIfUp(std::vector<void*>* params) {
		BallStatus* bs = ((BallStatus*)params->at(0));
		bool* up = ((bool*)params->at(2));
		if (bs->position.x < 155)
			up[0] = true;

	}

	static void calcPositionsVectorial(BallStatus* b, float yOffset = 0,
			Vec2* keeperPositionalVector = 0, Vec2* defensePositionalVector = 0,
			Vec2* midfieldPositionalVector = 0, Vec2* offensePositionalVector =
					0) {

	}
};

#endif //CALCULATOR_HPP
