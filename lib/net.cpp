#include <enet/enet.h>

#include <net.h>
#include <io.h>
#include <string.h>

sta S CLI_ID = 0;
sta S MAX_PEERS = 150;

inl X new_cli_id() -> S {
	return CLI_ID++;
}

X Net::init() -> I {
	if (I e = enet_initialize() != 0) {
		elog("failed to initialize enet.");
		return e;
	}

//	atexit(enet_deinitialize);

	return 0;
}

Net::Srv::Srv(CC *a, I p) {
	enet_address_set_host(&addr, a);
	addr.port = p;
	srv = enet_host_create(&addr, MAX_PEERS, 2, 0, 0);

	if (srv == nullptr) {
		fatal("Cannot make enet host?? %s:%d", a, p);
	}
}

Net::Srv::~Srv() {
	enet_host_destroy(srv);
}

Net::Cli::Cli(C *a, I p) {
	S aL = strlen(a);
	ENetEvent e;

	enet_address_set_host(&addr, a);
	enet_address_get_host(&addr, a, aL);
	addr.port = p;

	cli = enet_host_create(nullptr, 1, 2, 0, 0);
	if (cli == nullptr) fatal("cannot create ENet client host.");

	peer = enet_host_connect(cli, &addr, 1, 0);
	if (peer == nullptr) fatal("no available peers.");

	if (
		enet_host_service(cli, &e, 5000) > 0
		&& e.type == ENET_EVENT_TYPE_CONNECT
	) {
		log_("connection to %s:%d succeeded", a, p);
	} else {
		enet_peer_reset(peer);
		elog("failed to connect to %s:%d", a, p);
	}
}

Net::Cli::~Cli() {
	enet_host_destroy(cli);
	enet_peer_disconnect(peer, 0);
	enet_peer_reset(peer);
}
