#include <optional>
#include <format>
#include <SDL3/SDL.h>

#include <u.h>
#include <gfx.h>
#include <fs.h>

S gfx::W = 640;
S gfx::H = 480;
bool gfx::OPEN = true;
std::mutex gfx::SDL_X;

Vec2 gfx::mouse::POS = Vec2(0.0, 0.0);
std::mutex gfx::mouse::POS_X;

SDL_Window *gfx::win::WIN;
SDL_Renderer *gfx::win::REN;
I gfx::win::W = 640;
I gfx::win::H = 480;
CC *gfx::win::TITLE = "mob with friends!";
std::mutex gfx::win::WIN_X;

gfx::Texs gfx::TEXS;
std::mutex gfx::TEXS_X;

X gfx::init(CC *n) -> bool {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	X G = X_G(win::WIN_X);
	if (!SDL_CreateWindowAndRenderer(
		win::TITLE,
		win::W, win::H,
		SDL_WINDOW_HIDDEN,
		&win::WIN, &win::REN
	)) {
		elog("SDL_CreateWindowAndRenderer: {}", SDL_GetError());
		return false;
	}

	if (!win::WIN || !win::REN) {
		elog("win::WIN==nullptr||win::REN==nullptr");
		return false;
	}

	return true;
}

X gfx::close() -> V {
	X G = X_G(win::WIN_X);
	OPEN = false;
	SDL_DestroyRenderer(win::REN);
	SDL_DestroyWindow(win::WIN);
	SDL_Quit();
}

X gfx::close(int) -> V {
	return gfx::close();
}

X gfx::Texs::load_bmp_dir(std::string p) -> std::optional<std::string> {
	X bmps = fs::bmp_files(p);
	for (X &i : bmps) {
		X bmp = SDL_LoadBMP(i.c_str());
		if (bmp == nullptr) {
			return std::format("failed to load bmp file {}", i);
		}

		X G = X_G(win::WIN_X);
		X txt = SDL_CreateTextureFromSurface(win::REN, bmp);
		SDL_DestroySurface(bmp);

		texs.push_back(txt);
		paths.push_back(i);
	}

	return {};
}

X gfx::clear(u8 r, u8 g, u8 b) -> std::optional<std::string> {
	X G = X_G(win::WIN_X);

	SDL_SetRenderDrawColor(win::REN, r, g, b, 0xaa);

	X clr = SDL_RenderClear(win::REN);
	if (!clr) {
		return std::optional<std::string>{
			std::format("err clearing win::REN: {}", SDL_GetError())
		};
	}

	SDL_RenderPresent(win::REN);

	return {};
}
