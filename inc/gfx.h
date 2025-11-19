#ifndef __TRHS_GFX_H__
#define __TRHS_GFX_H__

#include <mutex>
#include <vector>
#include <optional>
#include <string>
#include <SDL3/SDL.h>

#include <u.h>
#include <vec.h>

namespace gfx {
	extern S W, H;
	extern bool OPEN;
	namespace mouse {
		extern Vec2 POS;
		extern std::mutex POS_X;

		inl sta X pos() -> Vec2 {
			X G = std::lock_guard<std::mutex>(POS_X);
			return Vec2(POS.x, POS.y);
		}

		inl sta X set_pos(F x, F y) -> V {
			X G = std::lock_guard<std::mutex>(POS_X);
			POS = Vec2(x, y);
		}
	}

	namespace win {
		extern SDL_Window *WIN;
		extern SDL_Renderer *REN;
		extern I W, H;
		extern CC *TITLE;
		extern std::mutex WIN_X;
	}

	struct Texs {
		std::vector<SDL_Texture*> texs;
		std::vector<std::string> paths;

		std::optional<std::string> load_png_dir(std::string);
		std::optional<std::string> load_bmp_dir(std::string);

		inl Texs()
			: texs{std::vector<SDL_Texture*>()}
			, paths{std::vector<std::string>()}
		{
			#define BMP(x)({ \
				log_("loading \x1b[35m{}\x1b[0m", x); \
				load_bmp_dir(x); \
			})
			X bmp = BMP("ref/sprites/bmp/");
			if (bmp.has_value()) {
				elog(
					"error while loading bmp sprites {}",
					bmp.value()
				);
			}
		}

		inl Texs(con Texs &x) : texs{x.texs}, paths{x.paths} {}
		inl ~Texs() {
			for (S i = 0; i < texs.size(); i++) {
				SDL_DestroyTexture(texs[i]);
			}
		}

		inl X find(std::string x) -> std::optional<S> {
			S i = 0;
			for (X &p : paths) {
				if (p == x) {
					return i;
				}
				i++;
			}
			return {};
		}

		inl X get(std::string x) -> std::optional<SDL_Texture*> {
			X f = find(x);
			return f
				? std::optional<SDL_Texture*>(texs[*f])
				: std::nullopt;
		}
	};

	extern Texs TEXS;
	extern std::mutex TEXS_X;

	I init(CC *n);
	V close(int);
	V close();
	std::optional<std::string> clear(F r, F g, F b);

	template<typename F>
	inl X window(F f) -> V {
		while (gfx::OPEN) {
			f();
		}
	}
}

#endif
