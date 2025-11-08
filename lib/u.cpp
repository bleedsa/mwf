#include <enet/enet.h>
#include <u.h>
#include <gfx.h>
#include <net.h>

X U::init(CC *n) -> I {
	return (gfx::init(n) != 0) && (Net::init() != 0);
}

X U::init() -> I {
	return Net::init();
}
