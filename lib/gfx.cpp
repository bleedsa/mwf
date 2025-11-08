#include <u.h>
#include <gfx.h>

#include <raylib.h>

S gfx::W = 640;
S gfx::H = 480;

X gfx::init(CC *n) -> I {
	InitWindow(gfx::W, gfx::H, n);
	SetTargetFPS(60);
	return 0;
}

X gfx::close() -> V {
	CloseWindow();
}
