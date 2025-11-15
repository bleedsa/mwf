#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>

#include <ev.h>
#include <gfx.h>

inl X process_keys() -> V {
	X keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_SCANCODE_ESCAPE]) gfx::close();
}

X Ev::process() -> V {
	SDL_Event e;
	while (gfx::OPEN && SDL_PollEvent(&e)) {
		switch (e.type) {
		CASE(SDL_EVENT_MOUSE_MOTION, {
			gfx::mouse::set_pos(e.motion.x, e.motion.y);
		})
		}

		process_keys();
	}
}
