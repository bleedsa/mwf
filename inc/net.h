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

		/* send a packet with data D and length L */
		inl X send_packet(u8 *D, S L) -> V {
			ENetPacket *p = enet_packet_create(D, L, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, p);
			enet_host_flush(cli);
		}
	};
}

#endif
