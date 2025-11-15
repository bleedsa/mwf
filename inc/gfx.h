#ifndef __TRHS_GFX_H__
#define __TRHS_GFX_H__

#include <mutex>
#include <vector>
#include <SDL3/SDL.h>

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

	namespace win {
		extern SDL_Window *WIN;
		extern SDL_Renderer *REN;
		extern I W, H;
		extern std::mutex WIN_X;
	}

	struct Texs {
		std::vector<SDL_Texture*> texs;

		inl Texs() : texs{std::vector<SDL_Texture*>()} {}
		inl Texs(con Texs &x) : texs{x.texs} {}
		inl ~Texs() {
			for (S i = 0; i < texs.size(); i++) {
				SDL_DestroyTexture(texs[i]);
			}
		}
	};

	I init(CC *n);
	V close(int);
	V close();

	template<typename F>
	inl X window(F f) -> V {
		while (gfx::OPEN) {
			f();
		}
	}
}

#endif
