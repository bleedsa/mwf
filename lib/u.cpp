#include <enet/enet.h>

#include <u.h>
#include <gfx.h>
#include <net.h>

X U::init(CC *n) -> bool {
	return gfx::init(n) && Net::init();
}

X U::init() -> bool {
	return Net::init();
}
