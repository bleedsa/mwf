#include <u.h>
#include <net.h>
#include <gfx.h>

#include "win.h"

X win::main() -> I {
	log_("clear");
	X clr = gfx::clear(1.0, 1.0, 1.0);
	if (!clr) {
		elog("{}", clr.value());
		return -1;
	}
	return 0;
}
