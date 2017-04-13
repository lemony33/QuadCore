#pragma once

#include <iostream>//


template<class T>
class Vector3
{
public:
	union
	{
		struct { T x_, y_, z_; };
		T v_[3];
	};

	Vector3()
		: x_(T()), y_(T()), z_(T())
	{}

	Vector3(const T _x, const T _y, const T _z)
		: x_(_x), y_(_y), z_(_z)
	{}

	void set(const T& v0, const T& v1, const T& v2)
	{
		v_[0] = v0;
		v_[1] = v1;
		v_[2] = v2;
	}

	void operator *= (const T s)
	{
		x_ *= s;
		y_ *= s;
		z_ *= s;
	}

	friend std::ostream& operator<< (std::iostream& stream, const Vector3<T>& vec)
	{
		stream << vec.x_ << " " << vec.y_ << " " << vec.z_;
		return stream;
	}

	void print()
	{
		std::cout << x_ << " " << y_ << " " << z_;
	}
};
