#include <u.h>
#include <net.h>
#include <gfx.h>

#include "win.h"

X win::main() -> I {
	log_("clear");
	X clr = gfx::clear(0xff, 0xff, 0xff);
	if (!!clr) {
		elog("{}", *clr);
	}
	return 0;
}
