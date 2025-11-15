#include <SDL3/SDL.h>

#include <u.h>
#include <gfx.h>

S gfx::W = 640;
S gfx::H = 480;

bool gfx::OPEN = true;

Vec2 gfx::mouse::POS = Vec2(0.0, 0.0);
std::mutex gfx::mouse::POS_X;

SDL_Window *gfx::win::WIN;
SDL_Renderer *gfx::win::REN;
std::mutex gfx::win::WIN_X;

I gfx::win::W = 640;
I gfx::win::H = 480;

X gfx::init(CC *n) -> I {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	X G = std::lock_guard<std::mutex>(win::WIN_X);
	win::WIN = SDL_CreateWindow(n, win::W, win::H, 0);
	win::REN = SDL_CreateRenderer(win::WIN, nullptr);

	return 0;
}

X gfx::close() -> V {
	OPEN = false;
	X G = std::lock_guard<std::mutex>(win::WIN_X);
	SDL_DestroyWindow(win::WIN);
	SDL_DestroyRenderer(win::REN);
	SDL_Quit();
}

X gfx::close(int) -> V {
	return gfx::close();
}
