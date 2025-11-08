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
		ENetAddress addr;
		ENetEvent ev;
		ENetHost *cli;
		ENetPeer *peer;

		Cli(CC *addr, I port);
		~Cli();
	};
}

#endif
