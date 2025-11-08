#include <enet/enet.h>

#include <net.h>
#include <io.h>

X Net::init() -> I {
	if (I e = enet_initialize() != 0) {
		elog("failed to initialize enet.");
		return e;
	}

//	atexit(enet_deinitialize);

	return 0;
}

Net::Srv::Srv(CC *a, I p) {
	srv = enet_host_create(nullptr, 32, 2, 0, 0);

	if (srv == nullptr) {
		fatal("Cannot make enet host?? %s:%d", a, p);
	}
}

Net::Srv::~Srv() {
	enet_host_destroy(srv);
}

Net::Cli::Cli(CC *a, I p) {
	cli = enet_host_create(NULL, 1, 2, 0, 0);
	if (cli == nullptr) fatal("cannot make enet host?? %s:%d", a, p);

	enet_address_set_host(&addr, a);
	addr.port = p;

	peer = enet_host_connect(cli, &addr, 1, 0);
	if (peer == nullptr) fatal("no available peers");
}

Net::Cli::~Cli() {
	enet_host_destroy(cli);
}
