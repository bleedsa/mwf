#include <SDL3/SDL.h>

#include <u.h>
#include <gfx.h>
#include "win.h"

std::mutex win::WIN_X;

X win::open() -> I {
	log_("win::open()");

	X G = X_G(win::WIN_X);
	win::WIN_T = WIN_MAIN;

	X G_ = X_G(gfx::win::WIN_X);
	if (!SDL_ShowWindow(gfx::win::WIN)) {
		elog("SDL_ShowWindow(): {}", SDL_GetError());
		return -1;
	}

	return 0;
}
