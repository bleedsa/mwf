#ifndef __MWF_NET_H__
#define __MWF_NET_H__

#include <optional>
#include <tuple>
#include <cstring>

#include <u.h>
#include <enet/enet.h>

namespace Net {
	bool init();

	struct Srv {
		ENetAddress addr;
		ENetHost *srv;

		Srv(CC *addr, I port);
		~Srv();

		/* send a packet with data D and length L */
		inl X send_packet(ENetPeer *peer, u8 *D, S L) -> V {
			ENetPacket *p = enet_packet_create(D, L, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, p);
			enet_host_flush(srv);
		}
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

		inl X recv_packet() -> std::optional<std::tuple<S, u8*>> {
			ENetEvent e;
			if (enet_host_service(cli, &e, 1000) > 0) {
				if (e.type == ENET_EVENT_TYPE_RECEIVE) {
					X L = e.packet->dataLength;
					X P = new u8[L];
					memmove(P, e.packet->data, L);
					enet_packet_destroy(e.packet);
					return std::tie(L, P);
				}
			}
			return {};
		}
	};
}

#endif
