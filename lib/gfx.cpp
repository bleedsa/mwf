#include <optional>
#include <format>
#include <SDL3/SDL.h>

#include <u.h>
#include <gfx.h>
#include <fs.h>

S gfx::W = 640;
S gfx::H = 480;

bool gfx::OPEN = true;

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

X gfx::init(CC *n) -> I {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	X G = std::lock_guard<std::mutex>(win::WIN_X);
	if (!SDL_CreateWindowAndRenderer(
		win::TITLE,
		win::W, win::H,
		SDL_LOGICAL_PRESENTATION_LETTERBOX,
		&win::WIN, &win::REN
	)) {
		return -1;
	}

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

X gfx::Texs::load_bmp_dir(std::string p) -> std::optional<std::string> {
	X bmps = fs::bmp_files(p);
	for (X &i : bmps) {
		X bmp = SDL_LoadBMP(i.c_str());
		if (bmp == nullptr) {
			return std::format("failed to load bmp file {}", i);
		}

		X G = std::lock_guard<std::mutex>(win::WIN_X);
		X txt = SDL_CreateTextureFromSurface(win::REN, bmp);
		SDL_DestroySurface(bmp);

		texs.push_back(txt);
		paths.push_back(i);
	}

	return {};
}

X gfx::clear(F r, F g, F b) -> std::optional<std::string> {
	X G = X_G(win::WIN_X);

	SDL_SetRenderDrawColorFloat(win::REN, r, g, b, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderClear(win::REN);
	SDL_RenderPresent(win::REN);

	return {};
}
