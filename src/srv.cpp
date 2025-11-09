#include <u.h>
#include <net.h>

X main(I argc, C **argv) -> I {
	U::init();

	X srv = Net::Srv("0.0.0.0", 6061);

	while (true) {
		ENetEvent ev;
		while (enet_host_service(srv.srv, &ev, 1000) > 0) {
			switch (ev.type) {
			case ENET_EVENT_TYPE_NONE:
				continue;

			case ENET_EVENT_TYPE_CONNECT:
				log(
					"new client from %x:%u\n",
					ev.peer->address.host,
					ev.peer->address.port
				   );
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				log("%s disconnected.", (C*)ev.peer->data);
				ev.peer->data = nullptr;
				break;
			}
		}
	}

	return 0;
}
