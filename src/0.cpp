#include <cstring>
#include <thread>
#include <mutex>
#include <csignal>

#include <u.h>
#include <gfx.h>
#include <ctrl.h>
#include <net.h>
#include <map.h>
#include <syn.h>
#include <ev.h>
#include "win/win.h"

Map::Map MAP(200, 200);
std::mutex MAP_X;

X get_map(C *ip) -> I {
	X cli = Net::Cli(ip, 6065);
	X opt = cli.recv_packet();
	if (opt.has_value()) {
		X [L, D] = opt.value();
		X G = std::lock_guard<std::mutex>(MAP_X);
		return 0;
	} else {
		return 1;
	}
}

X window() -> I {
	gfx::window(win::this_win);
	return 0;
}

X events() -> I {
	Ev::process();
	return 0;
}

X main(I argc, C **argv) -> I {
	ENetEvent ev;
	u8 *D = nullptr;

	if (argc < 2) fatal("usage: %s [ip]", argv[0]);
	std::signal(SIGINT, gfx::close);
	U::init(argv[0]);
	get_map(argv[1]);

	X t0 = syn::async(Ev::process);
	X t1 = syn::async<I>(window);
	X t2 = syn::async<I>([](C *ip){
		while (gfx::OPEN) get_map(ip);
		return 0;
	}, argv[1]);

	return 0;
}
