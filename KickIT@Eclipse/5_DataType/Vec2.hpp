/**
 * @file Vec2.hpp
 * @brief
 */
#ifndef VEC2_HPP_
#define VEC2_HPP_

#include <iostream>
#include <math.h>

/**Vec2 class
 *
 */
class Vec2 {
public:
	float x;
	float y;

	/**Vec2 function
	 *
	 */
	Vec2() {
		x = 0;
		y = 0;
	}

	/**Vec2 function
	 * @param (float _x, float _y)
	 */
	Vec2(float _x, float _y) {
		this->x = _x;
		this->y = _y;
	}

	/**update function
	 * @param (float newx, float newy)
	 */
	void update(float newx, float newy) {
		this->x = newx;
		this->y = newy;
	}

	/**toTarget function
	 * @param (const Vec2& destination)
	 * @return res
	 */
	Vec2 toTarget(const Vec2& destination){
		Vec2 res;
		res.x = destination.x - this->x;
		res.y = destination.y - this->y;
		return res;
	}

	/**update function
	 * @param (Vec2* newp)
	 */
	void update(Vec2* newp) {
		this->x = newp->x;
		this->y = newp->y;
		//delete newp;
	}

	/**dot function
	 * @param (const Vec2& v)
	 * scalarproduct = laenge1 * laenge2 * cos (angle between)
	 *
	 * @return this->x * v.x + this->y * v.y
	 */
	float dot(const Vec2& v) const {
		//skalarprodukt = laenge1 * laenge2 * cos(winkel dazwischen)
		return this->x * v.x + this->y * v.y;
	}

	/**cross function
	 * @param (const Vec2& v)
	 * @return this->x * v.y - v.x * this->y
	 */
	float cross(const Vec2& v) const {
		return this->x * v.y - v.x * this->y;
	}

	/**operator+ function
	 *@param (const Vec2& v)
	 *@return result
	 */
	Vec2 operator+(const Vec2& v) const {
		Vec2 result;
		result.x = this->x + v.x;
		result.y = this->y + v.y;
		return result;
	}

	/**operator- function
	 * @param (const Vec2& v)
	 * @return result
	 */
	Vec2 operator-(const Vec2& v) const {
		Vec2 result;
		result.x = this->x - v.x;
		result.y = this->y - v.y;
		return result;
	}

	/**operator+= function
	 * @param (const Vec2& v)
	 * @return *this
	 */
	Vec2& operator+=(const Vec2& v) {
		this->x = this->x + v.x;
		this->y = this->y + v.y;
		return *this;
	}

	/**operator* function
	 * @param (float c)
	 * @return result
	 */
	Vec2 operator*(float c) const {
		Vec2 result;
		result.x = this->x * c;
		result.y = this->y * c;
		return result;
	}

	/**operator- function
	 * @return result
	 */
	Vec2 operator-() const {
		Vec2 result;
		result.x = this->x * (-1);
		result.y = this->y * (-1);
		return result;
	}

	/**lengthSquared function
	 * @return lengthSquared
	 */
	float lengthSquared() const {
		float lengthSquared = this->x * this->x + this->y * this->y;
		return lengthSquared;
	}

	/**length function
	 * @return sqrtf(this->lengthSquared())
	 */
	float length() const {
		return sqrtf(this->lengthSquared());
	}

	/**normalize function
	 * @return *this
	 */
	Vec2& normalize() {
		float length = this->length();
		if (!(length == 0)) {
			float factor = 1 / length;
			this->x = this->x * factor;
			this->y = this->y * factor;
		}
		//else std::cout << "nullVec2" << std::endl;
		return *this;
	}

	/**reflection function
	 * @param (const Vec2& normal)
	 * @return result
	 */
	Vec2 reflection(const Vec2& normal) const {
		float lengthOfProjection = this->dot(normal);
		Vec2 reflectionImpulse = normal * lengthOfProjection;
		reflectionImpulse = reflectionImpulse * 2;
		Vec2 result = *this - reflectionImpulse;
		return result;
	}

	/**equals function
	 * @param (const Vec2 v)
	 * @return this->x == v.x && this->y == v.y
	 */
	bool equals(const Vec2 v){
		return this->x == v.x && this->y == v.y;
	}

	/**setLength function
	 * @param (float millimetersPerSecond)
	 */
	void setLength(float millimetersPerSecond){
		float factor = millimetersPerSecond/this->length();
		this->x *= factor;
		this->y *= factor;
	}
};

#endif /* VEC2_HPP_ */
