#include <u.h>
#include <gfx.h>
#include <ctrl.h>
#include <net.h>
#include "win/win.h"

I main(I argc, C **argv) {
	U::init(argv[0]);

	X cli = Net::Cli(argv[1], 6061);

	/*
	gfx::window(win::this_win);
	gfx::close();
	*/
	return 0;
}
