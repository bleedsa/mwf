#include <string.h>

#include <u.h>
#include <gfx.h>
#include <ctrl.h>
#include <net.h>
#include "win/win.h"

I main(I argc, C **argv) {
	if (argc < 2) fatal("usage: %s [ip]", argv[0]);

	U::init(argv[0]);

	X cli = Net::Cli(argv[1], 6061);
	X msg = "hello world";
	cli.send_packet((u8*)msg, strlen(msg)+1);

	gfx::window(win::this_win);
	gfx::close();
	return 0;
}
