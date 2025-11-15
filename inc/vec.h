#ifndef __MWF_VEC_H__
#define __MWF_VEC_H__

#include <u.h>

struct Vec2 {
	F x;
	F y;

	inl Vec2(F x, F y)    : x{x},   y{y}   {}
	inl Vec2(con Vec2 &x) : x{x.x}, y{x.y} {}
	inl X operator=(con Vec2 &x) -> con Vec2& {
		this->x = x.x, y = x.y;
		return *this;
	}
};

#endif
