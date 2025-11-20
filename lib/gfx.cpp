#include <optional>
#include <format>
#include <SFML/Graphics.hpp>

#include <u.h>
#include <gfx.h>
#include <fs.h>

S gfx::W = 640;
S gfx::H = 480;
bool gfx::OPEN = true;
std::mutex gfx::SDL_X;

Vec2 gfx::mouse::POS = Vec2(0.0, 0.0);
std::mutex gfx::mouse::POS_X;

sf::RenderWindow gfx::win::WIN;
I gfx::win::W = 640;
I gfx::win::H = 480;
CC *gfx::win::TITLE = "mob with friends!";
std::mutex gfx::win::WIN_X;

X gfx::init(CC *n) -> bool {
	X G = X_G(win::WIN_X);

	return true;
}

X gfx::close() -> V {
	X G = X_G(win::WIN_X);
	OPEN = false;
}

X gfx::close(int) -> V {
	return gfx::close();
}
