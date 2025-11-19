#include <u.h>
#include "win.h"

std::mutex win::WIN_X;

X win::open() -> I {
	log_("win::open()");
	X G = std::lock_guard<std::mutex>(win::WIN_X);
	win::WIN_T = WIN_MAIN;
	return 0;
}
