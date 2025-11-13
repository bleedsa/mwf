#ifndef __TRHS_WIN_H__
#define __TRHS_WIN_H__

#include <u.h>

namespace win {
	I open(C *ip);
	I main(C *ip);

	/* win state */
	enum WinT {
		WIN_OPEN = 0,
		WIN_MAIN,
	};

	extern WinT WIN_T;

	sta I (*WIN_FS[])(C*) = {
		[WIN_OPEN]=open,
		[WIN_MAIN]=main,
	};

	inl sta X this_win(C *ip) -> I {
		I (*f)(C*) = WIN_FS[WIN_T];
		return f(ip);
	}
}

#endif
