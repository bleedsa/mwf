#include <string.h>

#include <u.h>
#include <gfx.h>
#include <ctrl.h>
#include <net.h>
#include <map.h>
#include "win/win.h"

Map::Map MAP(200, 200);

I main(I argc, C **argv) {
	ENetEvent ev;
	u8 *D = nullptr;
	if (argc < 2) fatal("usage: %s [ip]", argv[0]);

	U::init(argv[0]);

	X cli = Net::Cli(argv[1], 6061);
	X hello = "hello world";

	cli.send_packet((u8*)hello, strlen(hello)+1);
	X p = cli.recv_packet();
	if (p.has_value()) {
		X [L, D] = p.value();
		log_("[%zu] %s", L, D);
	}

	gfx::window(win::this_win);
	gfx::close();
	return 0;
}
