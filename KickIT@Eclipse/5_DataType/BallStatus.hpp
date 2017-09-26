/**
 * @file BallStatus.hpp
 * @brief
 */
#ifndef BALLSTATUS_HPP_
#define BALLSTATUS_HPP_

#include "../5_DataType/Vec2.hpp"
#include <ctime>

/**BallStatus class
 *
 */
class BallStatus {
public:

	Vec2 movement;
	Vec2 position;
	clock_t last_update;

	/**BallStatus constructor
	 *
	 * @param (float posx, float posy, float movementx, float movementy)
	 */
	BallStatus(float posx, float posy, float movementx, float movementy) :
			movement(movementx, movementy), position(posx, posy), last_update() {

	}

	/**BallStatus constructor
	 *
	 */
	BallStatus() : movement(0.0f, 0.0f), position(0.0f, 0.0f), last_update() {
	}

	/**operator function
	 *
	 * @param (const BallStatus & bs)
	 *
	 * @return *this
	 */
	BallStatus & operator=(const BallStatus & bs) {
		this->movement.x = bs.movement.x;
		this->movement.y = bs.movement.y;

		this->position.x = bs.position.x;
		this->position.y = bs.position.y;

		return *this;
	}

	/**update function
	 *
	 * @param (float x, float y)
	 */
	void update(float x, float y){
		clock_t up_to_date = clock();
		double elapsed_secs = double(up_to_date - last_update) / CLOCKS_PER_SEC;
		last_update = up_to_date;

		/**newPos function
		 *
		 * @param (x,y)
		 */
		Vec2 newPos(x,y);

		//std::cout << "new pos x: " << x << " new y: " << y << std::endl;
		//std::cout << "elapsed: " << elapsed_secs << std::endl;
		this->movement = this->position.toTarget(newPos);
		//std::cout << "length: " << this->movement.length() << std::endl;

		this->movement.setLength(this->movement.length()/elapsed_secs);
		this->position.update(x,y);
	}
};

#endif //BALLSTATUS_HPP_
