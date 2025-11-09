#ifndef __MWF_NET_H__
#define __MWF_NET_H__

#include <u.h>
#include <enet/enet.h>

namespace Net {
	I init();

	struct Srv {
		ENetAddress addr;
		ENetHost *srv;

		Srv(CC *addr, I port);
		~Srv();
	};

	struct Cli {
		ENetHost *cli;
		ENetAddress addr;
		ENetEvent ev;
		ENetPeer *peer;

		Cli(C *addr, I port);
		~Cli();
	};
}

#endif
