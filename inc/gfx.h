#ifndef __TRHS_GFX_H__
#define __TRHS_GFX_H__

#include <mutex>
#include <vector>
#include <optional>
#include <string>
#include <SFML/Graphics.hpp>

#include <u.h>
#include <vec.h>

namespace gfx {
	extern S W, H;
	extern bool OPEN;
	extern std::mutex SDL_X;
	
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

	namespace win {
		extern sf::RenderWindow WIN;
		extern I W, H;
		extern CC *TITLE;
		extern std::mutex WIN_X;
	}

	bool init(CC *n);
	V close(int);
	V close();
	std::optional<std::string> clear(u8 r, u8 g, u8 b);

	template<typename F>
	inl X window(F f) -> V {
		while (gfx::OPEN) {
			f();
		}
	}
}

#endif
