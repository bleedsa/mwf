#ifndef __MWF_EV_H__
#define __MWF_EV_H__

#include <SDL3/SDL_events.h>

#include <gfx.h>

namespace Ev {
	inl X process() -> V {
		SDL_Event e;
		while (gfx::OPEN && SDL_PollEvent(&e)) {
			switch (e.type) {
			CASE(SDL_EVENT_MOUSE_MOTION, {
				gfx::mouse::set_pos(e.motion.x, e.motion.y);
			})
			}
		}
	}
}

#endif
