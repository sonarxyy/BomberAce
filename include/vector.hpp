/*
 * Reference: https://github.com/RedTopper/Super-Haxagon/blob/master/source/Core/Vector.hpp
 */


#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <algorithm>

namespace Vector {
	template <typename T>
	inline T ease(T time) { // For easing in and out effects
		time = std::clamp(time, static_cast<T>(0), static_cast<T>(1));
		T f = 0;
		if (time < static_cast<T>(0.5)) { // Ease in
			f = static_cast<T>(2) * time * time;
		}
		else { // Ease out
			time -= static_cast<T>(0.5);
			f = static_cast<T>(2) * time * (static_cast<T>(1) - time) + static_cast<T>(0.5);
		}
		return f;
	}

	template<typename T>
	inline T interpolate(T start, T end, T time) {
		return (end - start) * time + start;
	}

	template<typename T>
	struct Vector2 {
		T x;
		T y;

		Vector2() : x(0), y(0) {};
		explicit Vector2(T xPos) : x(xPos), y(xPos) {};
		Vector2(T xPos, T yPos) : x(xPos), y(yPos) {};

		Vector2 operator+(const Vector2& other) const {
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator*(const T& scalar) const {
			return Vector2(x * scalar, y * scalar);
		}
	};

	template<typename T>
	struct Vector3 {
		T x;
		T y;
		T z;

		Vector3() : x(0), y(0), z(0) {}
		explicit Vector3(Vector2<T> v) : x(v.x), y(v.y), z(0) {}
		explicit Vector3(T xPos) : x(xPos), y(xPos), z(xPos) {}
		Vector3(T xPos, T yPos, T zPos) : x(xPos), y(yPos), z(zPos) {}

		Vector3 operator+(const Vector3& v) const {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 operator*(const T& scalar) const {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		Vector3& normalize() {
			if (T n = norm(); n > 0) {
				T factor = 1 / n;
				x *= factor, y *= factor, z *= factor;
			}
			return *this;
		}

		T dot(const Vector3& scalar) const {
			auto mult = *this * scalar;
			return mult.x + mult.y + mult.z;
		}

		T norm() const {
			return sqrt(x * x + y * y + z * z);
		}

		Vector3 interpolate(Vector3 scalar, T time) const {
			return {
				Vector::interpolate<T>(x, scalar.x, time),
				Vector::interpolate<T>(y, scalar.y, time),
				Vector::interpolate<T>(z, scalar.z, time),
			};
		}

		Vector3 ease(Vector3 scalar, T time) const {
			return interpolate(scalar, Vector::ease<T>(time));
		}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector3<float> Vector3f;
}


#endif