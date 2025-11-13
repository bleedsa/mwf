#ifndef __TRHS_GFX_H__
#define __TRHS_GFX_H__

#include <u.h>
#include <raylib.h>

namespace gfx {
	extern S W, H;

	I init(CC *n);
	V close();

	template<typename F>
	inl X window(F f, C *ip) -> V {
		while (!WindowShouldClose()) {
			BeginDrawing(); {
				f(ip);
			}; EndDrawing();
		}
		close();
	}
}

#endif
