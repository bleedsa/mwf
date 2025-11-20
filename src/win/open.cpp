#include <u.h>
#include <gfx.h>
#include "win.h"

X win::open() -> I {
	log_("win::open()");

	X G = X_G(win::WIN_X);
	win::WIN_T = WIN_MAIN;

	X G_ = X_G(gfx::win::WIN_X);

	return 0;
}
