#ifndef __TRHS_GFX_H__
#define __TRHS_GFX_H__

#include <mutex>
#include <SDL3/SDL_init.h>

#include <u.h>
#include <vec.h>

namespace gfx {
	extern S W, H;
	extern bool OPEN;
	namespace mouse {
		extern Vec2 POS;
		extern std::mutex POS_X;

		inl sta X pos() -> Vec2 {
			X G = std::lock_guard<std::mutex>(POS_X);
			return Vec2(POS.x, POS.y);
		}

		inl sta X set_pos(F x, F y) -> V {
			X G = std::lock_guard<std::mutex>(POS_X);
			POS = Vec2(x, y);
		}
	}

	I init(CC *n);
	V close(int);

	template<typename F>
	inl X window(F f) -> V {
		while (gfx::OPEN) {
			f();
		}
	}
}

#endif
