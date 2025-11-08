#include <u.h>
#include <raylib.h>
#include "win.h"

X win::open() -> I {
	ClearBackground(RAYWHITE);
	log("win::open()");
	win::WIN_T = WIN_MAIN;
	return 0;
}
