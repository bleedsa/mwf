#include <msgpack.hpp>
#include <mutex>
#include <thread>

#include <u.h>
#include <net.h>
#include <map.h>

X MAP = Map::Map(460, 480);

X main(I argc, C **argv) -> I {
	U::init();

	X srv = Net::Srv("127.0.0.1", 6065);

	for (;;) {
		ENetEvent ev;
		while (enet_host_service(srv.srv, &ev, 1000) > 0) {
			switch (ev.type) {
			case ENET_EVENT_TYPE_NONE:
				continue;

			case ENET_EVENT_TYPE_CONNECT:
				log_(
					"new client \x1b[33m[{:#10x}:{}]\x1b[0m",
					ev.peer->address.host,
					ev.peer->address.port
				   );
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				log_("client {} disconnected", (C*)ev.peer->data ?: "null");
				ev.peer->data = nullptr;
				break;

			case ENET_EVENT_TYPE_RECEIVE:
				log_(
					"packet L:{},D:{},from:{},chan:{}",
					ev.packet->dataLength,
					(C*)ev.packet->data,
					(C*)ev.peer->data,
					ev.channelID
				);
				/*
				msgpack::sbuffer buf;
				MAP.pack(buf);
				*/
				enet_packet_destroy(ev.packet);

				break;
			}
		}
	}

	return 0;
}
