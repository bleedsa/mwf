#include <SDL3/SDL_init.h>

#include <u.h>
#include <gfx.h>

S gfx::W = 640;
S gfx::H = 480;
bool gfx::OPEN = true;
Vec2 gfx::mouse::POS = Vec2(0.0, 0.0);
std::mutex gfx::mouse::POS_X;

X gfx::init(CC *n) -> I {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	return 0;
}

X gfx::close(int) -> V {
	OPEN = false;
	SDL_Quit();
}
